#include "uart.h"
#include "servo.h"
#include "string.h"
#include "command_decoder.h"


int main (){

	extern struct Token asToken[MAX_TOKEN_NR];
	extern unsigned char ucTokenNr;
	//char cReceivedCommand [RECIEVER_SIZE];
	
	
	
	ServoInit(50);
	UART_InitWithInt(9600);

	
	while(1){
		
		if (Transmiter_GetStatus() == FREE){
			Transmiter_SendString("test123");		
	
		}	
	}
}

