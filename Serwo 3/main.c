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

/**********************************************/

int main (){
	KeyboardInit();
	DetectorInit();
	ServoInit(50);

	
	while(1){
	 	switch(eKeyboardRead()){
			
			case BUTTON_0:
					ServoCallib();
			break;
			
			case BUTTON_1:
					ServoGoTo(12);
			break;
			
			case BUTTON_2:
					ServoGoTo(24);
			break;
			
			case BUTTON_3:
					ServoGoTo(36);
			break;
			
			case RELASED:
			break;
		}
	}
}

