#include "led.h"
#include "keyboard.h"

void delay(int iMiliSeconds){
	int iDelayMaker;
	int iLoopsPerSeconds=iMiliSeconds*2380;
	for(iDelayMaker=0;iDelayMaker<iLoopsPerSeconds;iDelayMaker++){
	}
}

int main(){
	LedInit();
	KeyboardInit();
	while(1){
		delay(1000);
		switch ( eKeyboardRead() ){
			case BUTTON_1:
					LedStepRight();
					break;
			case BUTTON_2:
					LedStepLeft();
					break;
			default:
					break;
		}
	}
}
