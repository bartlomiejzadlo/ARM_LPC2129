#include <LPC21xx.H>
#include "servo.h"
#include "led.h"
#include "timer_interrupts.h"

#define DETECTOR_PIN (1<<10)


struct Servo sServo;


void DetectorInit(void){
	IO0DIR = IO0DIR&(~DETECTOR_PIN);
}

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

void ServoCallib(void){
	sServo.eState = CALLIB;
	while(sServo.eState == CALLIB){}
}

void ServoInit(unsigned int uiServoFrequency){
	void ServoCallib();
	Timer0Interrupts_Init(1000000/uiServoFrequency,&Automat);
	LedInit();
	DetectorInit();
}

void ServoGoTo(unsigned int uiPosition){
	sServo.eState=IN_PROGRESS;
	sServo.uiDesiredPosition = uiPosition;
	while(sServo.eState == IN_PROGRESS){}
}
