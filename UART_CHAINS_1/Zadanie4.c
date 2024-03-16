#include "led.h"
#include "keyboard.h"



int main(){
	
	enum LedState{Led_Left, Led_Right};
	enum LedState eLedState = Led_Left;
	unsigned char ucStepCounter =0;
	
	LedInit();
	KeyboardInit();
	
	while(1){
		switch(eLedState){
			
			case Led_Left:
				break;
				
			case Led_Right:
			ucStepCounter++;
				if(ucStepCounter > 3){
						ucStepCounter = 0;
						eLedState = Led_Left;
				}else{
						LedStepRight();
				}
				break;					
			}
		delay(1000);
	}
}

