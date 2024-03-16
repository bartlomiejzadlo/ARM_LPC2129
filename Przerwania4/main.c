#include "led.h"
#include "timer_interrupts.h"

/**********************************************/
int main (){
	unsigned int iMainLoopCtr;
	Timer0Interrupts_Init(25000,&LedStepLeft);
	LedInit();
	
	while(1){
	 	iMainLoopCtr++;
		iMainLoopCtr++;
		iMainLoopCtr++;
		iMainLoopCtr++;
	}
}
