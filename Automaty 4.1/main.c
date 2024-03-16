#include "led.h"
#include "keyboard.h"



int main(){
	
	enum LedState{Led_Left, Led_Right};
	enum LedState eLedState = Led_Right;
	unsigned char ucStepCounter =0;
	
	LedInit();
	KeyboardInit();
	
	while(1){
		switch(eLedState){
			
			case Led_Left:
				eLedState = Led_Left;
			break;
				
			case Led_Right:
				if(ucStepCounter > 3){
						ucStepCounter = 0;
						eLedState = Led_Left;
				}else{
						LedStepRight();
						eLedState = Led_Right;
				}
				ucStepCounter++;
			break;					
			}
		delay(4000);
	}
}

