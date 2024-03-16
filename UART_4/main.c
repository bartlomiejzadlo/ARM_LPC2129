#include "uart.h"
#include "led.h"
#include "servo.h"
#include "keyboard.h"



int main (){

	extern char cOdebranyZnak;
	unsigned char ucPozycjaWskaznika;
	unsigned char ucStop;
	
	ServoInit(50);
	UART_InitWithInt(9600);

	LedInit();
	

	while(1){
		
				
		switch(cOdebranyZnak){
			
			case '1':
				ucStop = 0;
				if(ucStop == 0){
					ucPozycjaWskaznika++;
					ServoGoTo(12*ucPozycjaWskaznika);
					ucStop = 0;
				}else{

				}
				
			break;
			
			case 'c':
				ServoCallib();
			break;
			
			default:{}
			
		}
		ucStop = 1;
		
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
