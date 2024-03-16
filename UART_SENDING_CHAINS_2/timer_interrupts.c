#include <LPC21xx.H>
#include "timer_interrupts.h"

// TIMER
#define mCOUNTER_ENABLE 0x00000001
#define mCOUNTER_RESET  0x00000002

// CompareMatch
#define mINTERRUPT_ON_MR0 0x00000001
#define mRESET_ON_MR0     0x00000002
#define mMR0_INTERRUPT    0x00000001

// VIC (Vector Interrupt Controller) VICIntEnable
#define VIC_TIMER0_CHANNEL_NR 4

// VICVectCntlx Vector Control Registers
#define mIRQ_SLOT_ENABLE 0x00000020

//Declaration of global variable
void(*ptrTimer0InterruptFunction)(void);

/**********************************************/
//(Interrupt Service Routine) of Timer 0 interrupt
__irq void Timer0IRQHandler(){

	T0IR=mMR0_INTERRUPT; 	 
	ptrTimer0InterruptFunction();		
	VICVectAddr=0x00; 	
}
/**********************************************/
void Timer0Interrupts_Init(unsigned int uiPeriod, void(*ptrInterruptFunction)(void)){ //unsigned int uiPeriod musimy wyrazac w mikrosekundach a 1 sekunda to 1000000 mikrosekund dlatego mamy wpisane Timer0Interrupts_Init(1000000,&WatchUpdate); 

	ptrTimer0InterruptFunction = ptrInterruptFunction;
	
        // interrupts

	VICIntEnable |= (0x1 << VIC_TIMER0_CHANNEL_NR);            
	VICVectCntl0  = mIRQ_SLOT_ENABLE | VIC_TIMER0_CHANNEL_NR;  
	VICVectAddr0  =(unsigned long)Timer0IRQHandler; 	   

        // match module

	T0MR0 = 15 * uiPeriod;   //bo czestotliwosc tktowania timera jest rowna 1/4 czestotliwosci taktowania procesora f=60/4=15 a wiemy ze okres to T=1/f czyli u nas T = 1/15M = 1u/15 aby wyrazic w jednej mikrosekundzie musimy pomnozyc razy 15 i mamy (1*u/15)*15=1*us              	      
	T0MCR |= (mINTERRUPT_ON_MR0 | mRESET_ON_MR0); 

        // timer

	T0TCR |=  mCOUNTER_ENABLE;  

}
