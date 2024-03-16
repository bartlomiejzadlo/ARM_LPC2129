#include "uart.h"
#include "led.h"
#include "servo.h"
#include "keyboard.h"


int main (){

	extern char cOdebranyZnak;
	unsigned char ucPozycjaWskaznika;
	
	ServoInit(50);
	UART_InitWithInt(9600);

	LedInit();
	

	while(1){
		
				
		switch(cOdebranyZnak){
			
			case '1':
				ucPozycjaWskaznika++;
				ServoGoTo(12*ucPozycjaWskaznika);
				cOdebranyZnak=NULL;
			break;
			
			case 'c':
				ServoCallib();
				ucPozycjaWskaznika = 0;
				cOdebranyZnak=NULL;
			break;
			
			default:{}
			
		}
		
		switch(eKeyboardRead()){
			
			case BUTTON_0:
					ServoCallib();
			break;
			
			case BUTTON_1:
					ServoGoTo(12);
			break;
			
			case BUTTON_2:
					ServoGoTo(24);
			break;
			
			case BUTTON_3:
					ServoGoTo(36);
			break;
			
			case RELASED:
			break;
		}
	}
}
