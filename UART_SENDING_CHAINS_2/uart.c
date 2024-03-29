#include <LPC210X.H>
#include "uart.h"
#include "string.h"

/************ UART ************/

// PIN CONNECT BLOCK
#define mP01_RX0_P01_PIN_CONNECT 1<<2
#define mP01_TX0_P01_PIN_CONNECT 1<<0 //ustawienie odpowiedniego pinu do pracy jako wyjscie nadajnika (z manuala/DOKUMENTACJI PROCESORA PIN CONNECT BLOCK)


// U0LCR Line Control Register
#define mDIVISOR_LATCH_ACCES_BIT                   0x00000080
#define m8BIT_UART_WORD_LENGTH                     0x00000003

// UxIER Interrupt Enable Register
#define mRX_DATA_AVALIABLE_INTERRUPT_ENABLE        0x00000001
#define mTHRE_INTERRUPT_ENABLE                     0x00000002

// UxIIR Pending Interrupt Identification Register
#define mINTERRUPT_PENDING_IDETIFICATION_BITFIELD  0x0000000F
#define mTHRE_INTERRUPT_PENDING                    0x00000002
#define mRX_DATA_AVALIABLE_INTERRUPT_PENDING       0x00000004

/************ Interrupts **********/
// VIC (Vector Interrupt Controller) channels
#define VIC_UART0_CHANNEL_NR  6
#define VIC_UART1_CHANNEL_NR  7

// VICVectCntlx Vector Control Registers
#define mIRQ_SLOT_ENABLE                           0x00000020

////////////// Zmienne globalne ////////////
char cOdebranyZnak;


///////////////////////////////////////////


struct TransmiterBuffer sTransmiterBuffer;

char Transmiter_GetCharacterFromBuffer(void){
	
	unsigned char ucCurrentSign;
	ucCurrentSign = sTransmiterBuffer.cData[sTransmiterBuffer.cCharCtr];
	
	if(ucCurrentSign == NULL){
		if(sTransmiterBuffer.fLastCharacter == 0){
			sTransmiterBuffer.fLastCharacter = 1;
			//sTransmiterBuffer.cCharCtr = 0;
			ucCurrentSign = '\r';
			return(ucCurrentSign);
		}else{
		sTransmiterBuffer.fLastCharacter = 0;
		sTransmiterBuffer.eStatus=FREE;
		return(ucCurrentSign);
		}
	}else{
		sTransmiterBuffer.cCharCtr++;
		return(ucCurrentSign);
	}
}


enum eTransmiterStatus Transmiter_GetStatus(void){

	return(sTransmiterBuffer.eStatus);
	
}


void Transmiter_SendString(char cString[]){ 
	
	sTransmiterBuffer.eStatus=BUSY;
	sTransmiterBuffer.cCharCtr=0; 
	CopyString(cString, sTransmiterBuffer.cData); 
	U0THR = Transmiter_GetCharacterFromBuffer(); 

}



struct RecieverBuffer sRecieverBuffer;

void Reciever_PutCharacterToBuffer(char cCharacter){
	
		if(sRecieverBuffer.ucCharCtr == RECIEVER_SIZE){
			sRecieverBuffer.eStatus = OVERFLOW;
		}else if (cCharacter == TERMINATOR){
			sRecieverBuffer.cData[sRecieverBuffer.ucCharCtr] = NULL;
			sRecieverBuffer.eStatus = READY;
			sRecieverBuffer.ucCharCtr = 0;
		}else{
			sRecieverBuffer.cData[sRecieverBuffer.ucCharCtr] = cCharacter;
      sRecieverBuffer.ucCharCtr++;	
		}
}


enum eRecieverStatus eReciever_GetStatus(void){
	
		return(sRecieverBuffer.eStatus);
	
}


void Reciever_GetStringCopy(char * ucDestination){
	
		CopyString(sRecieverBuffer.cData, ucDestination);
		sRecieverBuffer.eStatus = EMPTY;

}

///////////////////////////////////////////
__irq void UART0_Interrupt (void) {
   // jesli przerwanie z odbiornika (Rx)
   
   unsigned int uiCopyOfU0IIR=U0IIR; 

   if      ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mRX_DATA_AVALIABLE_INTERRUPT_PENDING) // odebrano znak
   {
      cOdebranyZnak = U0RBR;
			Reciever_PutCharacterToBuffer(cOdebranyZnak);
   } 
   
   if ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mTHRE_INTERRUPT_PENDING)              
   {
      if(sTransmiterBuffer.eStatus == BUSY && sTransmiterBuffer.cData[sTransmiterBuffer.cCharCtr] != '\0'){
				U0THR = Transmiter_GetCharacterFromBuffer(); 
			}
   }

   VICVectAddr = 0; // Acknowledge Interrupt
}

////////////////////////////////////////////
void UART_InitWithInt(unsigned int uiBaudRate){

   // UART0
   PINSEL0 = PINSEL0 | mP01_RX0_P01_PIN_CONNECT | mP01_TX0_P01_PIN_CONNECT;                // ustawic pina na odbiornik uart0 //ustawic odpowiedni pin do pracy jako wyjscie nadajnika 
   U0LCR  |= m8BIT_UART_WORD_LENGTH | mDIVISOR_LATCH_ACCES_BIT; // dlugosc slowa, DLAB = 1
   U0DLL   = (((15000000)/16)/uiBaudRate);                      // predkosc transmisji
   U0LCR  &= (~mDIVISOR_LATCH_ACCES_BIT);                       // DLAB = 0
   U0IER  |= mRX_DATA_AVALIABLE_INTERRUPT_ENABLE | mTHRE_INTERRUPT_ENABLE;               // wlaczamy (globalne) przerwanie, poniewaz dane sa dostepne (odebrane i wpisane do bufora) // oraz odblokowac przerwania nadajnika (odpowiednia maska jest juz zdefiniowana).            //teraz odblokowujemy globalne przerwania zarowno na odbior znaku (pierwsza czesc/pierwszy if) jak i na wysylke (druga czesc/drugi if)

   // INT
   VICVectAddr1  = (unsigned long) UART0_Interrupt;             // set interrupt service routine address
   VICVectCntl1  = mIRQ_SLOT_ENABLE | VIC_UART0_CHANNEL_NR;     // use it for UART 0 Interrupt
   VICIntEnable |= (0x1 << VIC_UART0_CHANNEL_NR);               // Enable UART 0 Interrupt Channel
}






