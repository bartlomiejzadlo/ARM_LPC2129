#include "uart.h"
#include "servo.h"
#include "string.h"
#include "command_decoder.h"


int main (){

	extern struct Token asToken[MAX_TOKEN_NR];
	extern unsigned char ucTokenNr;
	char cHelperReadingArray [RECIEVER_SIZE];
	
	
	ServoInit(50);
	UART_InitWithInt(9600);

	
	
	while(1){
		
		if(eReciever_GetStatus() == READY){
			Reciever_GetStringCopy(cHelperReadingArray);
			DecodeMsg(cHelperReadingArray);
			if ((ucTokenNr != 0) && (asToken[0].eType == KEYWORD)){
				
				switch (asToken[0].uValue.eKeyword){
					
					case CALLIBRATION:
						
						ServoCallib();
					
					break;
					
					case GOTO:
						
						if (asToken[1].eType == NUMBER){
							ServoGoTo(asToken[1].uValue.uiNumber);
						}
					
					break;
							
					default:{}
						
					break;
					
				}
			}
		}
	}
}
	

