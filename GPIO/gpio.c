#include <LPC21xx.H>
#define LED0_bm 0x10000
#define LED1_bm 0x20000
#define LED2_bm 0x40000
#define LED3_bm 0x80000
#define BUT0_bm 0x10
#define BUT1_bm 0x40
#define BUT2_bm 0x20
#define BUT3_bm 0x80

void delay(int iMiliSeconds){
	int iDelayMaker;
	int iLoopsPerSeconds=iMiliSeconds*2380;
	for(iDelayMaker=0;iDelayMaker<iLoopsPerSeconds;iDelayMaker++){

}
}


void LedOn(unsigned char ucLedIndeks){
	IO1CLR = LED0_bm|LED1_bm|LED2_bm|LED3_bm;
	switch ( ucLedIndeks ){
    case 0:
				IO1SET = LED0_bm;
        break;
		case 1:
				IO1SET = LED1_bm;
        break;
		case 2:
				IO1SET = LED2_bm;
        break;
		case 3:
				IO1SET = LED3_bm;
        break;
    default:
				break;
		}
}

void LedInit(){
	IO1DIR =IO1DIR|LED0_bm|LED1_bm|LED2_bm|LED3_bm;
	IO1CLR = LED0_bm|LED1_bm|LED2_bm|LED3_bm;
	LedOn(0);
}

enum KeyboardState {RELASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};
enum KeyboardState eKeyboardRead(){
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

void KeyboardInit(){
	IO0DIR =IO0DIR&(~(BUT0_bm|BUT1_bm|BUT2_bm|BUT3_bm));
}

enum direction {LEFT,RIGHT};
void LedStep(enum direction eDirection){
	static unsigned int uiNumberOfDiode=0;
	if(eDirection==LEFT){
		uiNumberOfDiode++;
	}
	else if(eDirection==RIGHT){
		uiNumberOfDiode--;
	}
	LedOn(uiNumberOfDiode%4);
}

void LedStepLeft(){
	LedStep(LEFT);
}

void LedStepRight(){
	LedStep(RIGHT);
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
