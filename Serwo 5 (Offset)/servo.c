#include <LPC21xx.H>
#include "servo.h"
#include "led.h"
#include "timer_interrupts.h"

#define DETECTOR_PIN (1<<10)
#define SERVO_OFFSET 12


struct Servo sServo;


void DetectorInit(void){
	IO0DIR = IO0DIR&(~DETECTOR_PIN);
}

enum DetectorState eReadDetector(){
	if((IO0PIN & DETECTOR_PIN) == 0){
		return ACTIVE;
	}else{
		return INACTIVE;
	}
}

void Automat(){
	
	 switch(sServo.eState){
		 
		 static unsigned char ucShiftCounter = 0;
		 
			case CALLIB: 
				if(eReadDetector()== INACTIVE){
					LedStepRight();
					sServo.eState = CALLIB;
				}else{
					sServo.uiCurrentPosition = 0;
					sServo.uiDesiredPosition = 0;
					sServo.eState = SHIFT_OFFSET;
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
				
			 case SHIFT_OFFSET:
				 if(ucShiftCounter < SERVO_OFFSET){
					 LedStepRight();
					 ucShiftCounter++;
					 sServo.eState = SHIFT_OFFSET;
				 }else{
					 ucShiftCounter = 0;
					 sServo.eState = IDLE;
				 }
				break;
		}
}

void ServoInit(unsigned int uiServoFrequency){
	LedInit();
	sServo.eState = CALLIB;
	Timer0Interrupts_Init(1000000/uiServoFrequency,&Automat);
}

void ServoCallib(void){
	sServo.eState = CALLIB;
}

void ServoGoTo(unsigned int uiPosition){
	sServo.uiDesiredPosition = uiPosition;
	sServo.eState = IN_PROGRESS;
}
