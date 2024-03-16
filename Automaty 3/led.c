#include <LPC21xx.H>
#include "led.h"

#define LED0_bm (1<<16)
#define LED1_bm (1<<17)
#define LED2_bm (1<<18)
#define LED3_bm (1<<19)

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
	IO1DIR = IO1DIR|LED0_bm|LED1_bm|LED2_bm|LED3_bm;
	IO1CLR = LED0_bm|LED1_bm|LED2_bm|LED3_bm;
	LedOn(0);
}


void LedStep(enum kierunek eKierunek){
	static unsigned int uiNrDiody=0;
	if(eKierunek==LEWO){
		uiNrDiody++;
	}
	else if(eKierunek==PRAWO){
		uiNrDiody--;
	}
	LedOn(uiNrDiody%4);
}

void LedStepLeft(){
	LedStep(LEWO);
}

void LedStepRight(){
	LedStep(PRAWO);
}

void delay(int iMiliSeconds){
	int iDelayMaker;
	int iLoopsPerSeconds=iMiliSeconds*2380;
	for(iDelayMaker=0;iDelayMaker<iLoopsPerSeconds;iDelayMaker++){
	}
}
