#include "uart.h"
#include "led.h"
#include "servo.h"
//#include "keyboard.h"
#include "string.h"



int main (){

	extern char cOdebranyZnak;
	//unsigned char ucPozycjaWskaznika;
	char cHelperReadingArray [RECIEVER_SIZE];
	
	char cLeft [RECIEVER_SIZE] = "LEFT";
	char cRight [RECIEVER_SIZE] = "RIGHT";
	char cCallib [RECIEVER_SIZE] = "CALLIB";
	
	ServoInit(50);
	UART_InitWithInt(9600);

	LedInit();
	
	
	while(1){
			
		//Reciever_PutCharacterToBuffer ('l');
		//Reciever_PutCharacterToBuffer ('e');
		//Reciever_PutCharacterToBuffer ('f');
		//Reciever_PutCharacterToBuffer ('t');
		//Reciever_PutCharacterToBuffer (TERMINATOR);
		
		if(eReciever_GetStatus() == READY){
			Reciever_GetStringCopy(cHelperReadingArray);
			if(eCompareString(cHelperReadingArray, cCallib) == EQUAL){
				ServoCallib();
			}else if(eCompareString(cHelperReadingArray, cLeft) == EQUAL){
				ServoGoTo(50);
			}else if(eCompareString(cHelperReadingArray, cRight) == EQUAL){
				ServoGoTo(150);
			}
		}
	}
};
	

