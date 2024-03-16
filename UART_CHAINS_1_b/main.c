#include "uart.h"
#include "led.h"
#include "servo.h"
#include "keyboard.h"


int main (){

	extern char cOdebranyZnak;
	//unsigned char ucPozycjaWskaznika;
	
	ServoInit(50);
	UART_InitWithInt(9600);

	LedInit();
	
	
	while(1){

Reciever_PutCharacterToBuffer ('k');
Reciever_PutCharacterToBuffer ('o');
Reciever_PutCharacterToBuffer ('d');
Reciever_PutCharacterToBuffer (TERMINATOR);
		
	}
	
}
