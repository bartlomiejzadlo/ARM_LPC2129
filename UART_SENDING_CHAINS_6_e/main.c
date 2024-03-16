#include "uart.h"
#include "string.h"
#include "command_decoder.h"
#include "watch.h"
#include "timer_interrupts.h"
#include "servo.h"


int main (){

	extern struct Watch sWatch;
	extern struct Token asToken[MAX_TOKEN_NR];
	
	extern unsigned char ucTokenNr;
	unsigned char fCalcTokenDetected;
	unsigned char fNoCommandDetected;
	unsigned char fIDTokenDetected;
	
	char cReceivedCommand [RECIEVER_SIZE];
	char cReceivedTime [RECIEVER_SIZE];
	
	
	ServoInit(50);
	
	UART_InitWithInt(9600);
	Timer0Interrupts_Init(1000000, &WatchUpdate);

	
	while(1){
		
		if(eReciever_GetStatus() == READY){
			Reciever_GetStringCopy(cReceivedCommand);
			DecodeMsg(cReceivedCommand);
			if ((ucTokenNr != 0) && (asToken[0].uValue.eKeyword == CALC)){
				fCalcTokenDetected = 1;
			}else if((ucTokenNr != 0) && (asToken[0].uValue.eKeyword == ID)){
				fIDTokenDetected = 1;
			}else{
				fNoCommandDetected = 1;
			}
		}
		
		if (Transmiter_GetStatus() == FREE){
			if(sWatch.fSeccondsValueChanged == 1){		
				sWatch.fSeccondsValueChanged = 0;
				CopyString("sec ", cReceivedTime);
				AppendUIntToString(sWatch.ucSecconds, cReceivedTime);
				AppendString("\n", cReceivedTime);
				Transmiter_SendString(cReceivedTime);
			}else if(sWatch.fMinutesValueChanged == 1){
				sWatch.fMinutesValueChanged = 0;
				CopyString("min ", cReceivedTime);
				AppendUIntToString(sWatch.ucMinutes, cReceivedTime);
				AppendString("\n", cReceivedTime);
				Transmiter_SendString(cReceivedTime);
			}else if(fCalcTokenDetected == 1 && asToken[1].eType == NUMBER){
				fCalcTokenDetected = 0;
				CopyString("calc ", cReceivedTime);
				AppendUIntToString((asToken[1].uValue.uiNumber)* 2, cReceivedTime);
				AppendString("\n", cReceivedTime);
				Transmiter_SendString(cReceivedTime);
			}else	if (fIDTokenDetected == 1){ 
					fIDTokenDetected = 0;
					CopyString("ID ", cReceivedTime);
					AppendUIntToString(0x15000, cReceivedTime);
					AppendString("\n", cReceivedTime);
					Transmiter_SendString(cReceivedTime);
			}else	if (fNoCommandDetected == 1){
					fNoCommandDetected = 0;
					CopyString("Unkown Command\n", cReceivedTime);
					Transmiter_SendString(cReceivedTime);
			}
		}
	}	
}

