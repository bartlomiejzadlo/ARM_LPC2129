#include "uart.h"
#include "servo.h"
#include "string.h"
#include "command_decoder.h"




void Delay(unsigned int uiWaitMs){
	
	unsigned int uiCounter;
	unsigned int uiCounter2;
	
	for(uiCounter=0; uiCounter<uiWaitMs; uiCounter++){
	  for(uiCounter2=0; uiCounter2<1497; uiCounter2++){}
	}	
}



int main (){

	extern struct Token asToken[MAX_TOKEN_NR];
	extern unsigned char ucTokenNr;
	//char cReceivedCommand [RECIEVER_SIZE];
	
	
	
	ServoInit(50);
	UART_InitWithInt(9600);

	Transmiter_SendString("test123");
	
	
	while(1){
		
		Delay(500);
	}
}
	

