#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"
#include "timer_interrupts.h"

#define DETECTOR_PIN (1<<10) 

enum ServoState {CALLIB, IDLE, IN_PROGRESS};

struct Servo{
	enum ServoState eState; 
	unsigned int uiCurrentPosition; 
	unsigned int uiDesiredPosition;
};

struct Servo sServo;


	
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
	
	 switch(sServo.eState){
		 
			case CALLIB: 
				if(eReadDetector()== INACTIVE){
					LedStepRight();
					sServo.eState = CALLIB;
				}else{
					sServo.uiCurrentPosition = 0;
					sServo.uiDesiredPosition = 0;
					sServo.eState = IDLE;
				}
			break;
				
			case IDLE:
				if(sServo.uiCurrentPosition != sServo.uiDesiredPosition){
					sServo.eState = IN_PROGRESS;
				}else{
				sServo.eState = IDLE;
			}
			break;
			
			case IN_PROGRESS:
				if(sServo.uiCurrentPosition < sServo.uiDesiredPosition){
					LedStepRight();
					sServo.uiCurrentPosition++;
					sServo.eState = IN_PROGRESS;
				}else if(sServo.uiCurrentPosition > sServo.uiDesiredPosition){
					LedStepLeft();
					sServo.uiCurrentPosition--;
					sServo.eState = IN_PROGRESS;
				}else{
					sServo.eState = IDLE;
				}
			 break;
		}
}


/**********************************************/

int main (){
	Timer0Interrupts_Init(25000,&Automat);
	LedInit();
	KeyboardInit();
	DetectorInit();
	
	
	while(1){
	 	switch(eKeyboardRead()){
			
			case BUTTON_0:
					sServo.eState = CALLIB;
			break;
			
			case BUTTON_1:
					sServo.uiDesiredPosition = 12;
					sServo.eState = IN_PROGRESS;
			break;
			
			case BUTTON_2:
					sServo.uiDesiredPosition = 24;
					sServo.eState = IN_PROGRESS;
			break;
			
			case BUTTON_3:
					sServo.uiDesiredPosition = 36;
					sServo.eState = IN_PROGRESS;
			break;
			
			case RELASED:
			break;
		}
	}
}

