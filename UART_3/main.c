#include "uart.h"
#include "led.h"
#include "servo.h"
#include "keyboard.h"



int main (){

	extern char cOdebranyZnak;
	ServoInit(50);
	UART_InitWithInt(9600);
	LedInit();
	

	while(1){
		
		switch(cOdebranyZnak){
			case '1':
				ServoGoTo(12);
			break;
			
			case '2':
				ServoGoTo(24);
			break;
			
			case '3':
				ServoGoTo(36);
			break;
			
			
			case 'c':
				ServoCallib();
			break;
			
			default:{}
			
		}
		
		switch(eKeyboardRead()){
			
			case BUTTON_0:
					ServoCallib();
			break;
			
			case BUTTON_1:
					ServoGoTo(50);
			break;
			
			case BUTTON_2:
					ServoGoTo(100);
			break;
			
			case BUTTON_3:
					ServoGoTo(150);
			break;
			
			case RELASED:
			break;
		}
	}
}
