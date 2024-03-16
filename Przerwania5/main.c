#include "led.h"
#include "keyboard.h"
#include "timer_interrupts.h"

void Automat(){

	enum LedState{Led_Left, Led_Right, Led_Stop};
	static enum LedState eLedState = Led_Stop;
	
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
	}
}

/**********************************************/
int main (){
	unsigned int iMainLoopCtr;
	Timer0Interrupts_Init(250000,&Automat);
	LedInit();
	KeyboardInit();
	
	while(1){
	 	iMainLoopCtr++;
	}
}
