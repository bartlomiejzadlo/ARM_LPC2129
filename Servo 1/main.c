#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"
#include "timer_interrupts.h"

#define DETECTOR_PIN (1<<10) 


	
void DetectorInit(void){
	IO0DIR = IO0DIR&(~DETECTOR_PIN);
}

enum DetectorState {ACTIVE, INACTIVE};

enum DetectorState eReadDetector(){
	if((IO0PIN & DETECTOR_PIN) == 0){
		return ACTIVE;
	}
	else{
		return INACTIVE;
	}
}



void Automat(){

	enum LedState{Led_Left, Led_Right, Led_Stop, CALLIB};
	static enum LedState eLedState = CALLIB;
	

	
	 switch(eLedState){
		 
			case Led_Left:
				if(eKeyboardRead()==BUTTON_1){
					eLedState = Led_Stop;
				}else{
					LedStepLeft();
					eLedState = Led_Left;
				}
			break;
				
			case Led_Stop:
				if(eKeyboardRead()==BUTTON_2){
					eLedState = Led_Right;
				}else if(
					eKeyboardRead()==BUTTON_0){
					eLedState = Led_Left;
				}else{
					eLedState = Led_Stop;
				}
			break;
			
			case Led_Right:
				if(eKeyboardRead()==BUTTON_1){
					eLedState = Led_Stop;
				}else{
					LedStepRight();
					eLedState = Led_Right;
				}
			break;
				
			case CALLIB: 
				if(eReadDetector()== INACTIVE){
					LedStepRight();
					eLedState = CALLIB;
				}else{
					eLedState = Led_Stop;	
				}
			break;
	}
}

/**********************************************/

int main (){
	unsigned int iMainLoopCtr;
	Timer0Interrupts_Init(25000,&Automat);
	LedInit();
	KeyboardInit();
	DetectorInit();
	
	while(1){
	 	iMainLoopCtr++;
	}
}
