#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"

void Delay(int iMiliSeconds){
	int dTime;
	int x=iMiliSeconds*2380;
	for(dTime = 0; dTime<x ; dTime++){	
	}
}

int main(){
	
	enum LedState{LED_LEFT,LED_RIGHT,LED_STOP,WAIT,BLINK};
	enum LedState  eLedState = LED_STOP;

	unsigned char ucStepCounter=0;
	unsigned char ucBlinkLedState = 0;

	LedInit();
	KeyboardInit();

	while(1){
		switch(eLedState){
			case LED_RIGHT: 	
				if(eKeyboardRead()==BUTTON_1){
					eLedState = LED_STOP;
				}
				else{
					eLedState = LED_RIGHT;
					LedStepRight();
				}
				break;
			case LED_LEFT: 
				if(eKeyboardRead()==BUTTON_1){
					eLedState = LED_STOP;
				}
				else if(eKeyboardRead()==BUTTON_3){
					eLedState = BLINK;
				}
				else{
					LedStepLeft();
					eLedState = LED_LEFT;
				}
				break;
			case LED_STOP: 
				if(eKeyboardRead()==BUTTON_0){
					eLedState = LED_LEFT;
				}
				else if(eKeyboardRead()==BUTTON_2){
					eLedState = LED_RIGHT;
				}
				else{
					eLedState = LED_STOP;	
				}
				break;
			case WAIT: 
				if(eKeyboardRead()==BUTTON_0){
					eLedState = LED_RIGHT;
				}
				else{
					eLedState = WAIT;
					LedOn(3);
				}
				break;
			case BLINK: 	
				if(ucStepCounter > 10){
					ucStepCounter = 0;
					eLedState = WAIT;
				}
				else if(0 == ucBlinkLedState){
					LedOn(3);
					ucBlinkLedState = 1;
					eLedState = BLINK;
					ucStepCounter++;
				}
				else{
					LedOn(4); 
					ucBlinkLedState = 0;
					eLedState = BLINK;
}			
			break;
	 }
	 Delay(100);
	}
}