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
				if(eKeyboardRead()==BUTTON_0){
					eLedState = Led_Right;
				}else{
					eLedState = Led_Left;
				}
			break;
			
			case Led_Right: 
				ucStepCounter++;
				if(ucStepCounter > 3){
					ucStepCounter = 0;
					eLedState = Led_Left;
				}else{
					LedStepRight();
					eLedState = Led_Right;
				}
			break;	
	 }
	 delay(1000);
	}
}	

/*
enum ButtonState {RELASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};
enum ButtonState eKeyboardRead(){
		if((IO0PIN&BUT0_bm)==0){
			return BUTTON_0;
		}
		if((IO0PIN&BUT1_bm)==0){
			return BUTTON_1;
		}
		if((IO0PIN&BUT2_bm)==0){
			return BUTTON_2;
		}
		if((IO0PIN&BUT3_bm)==0){
			return BUTTON_3;
		}
		else{
			return RELASED;
		}
}
*/
