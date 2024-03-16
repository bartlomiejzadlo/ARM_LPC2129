#include "uart.h"
#include "servo.h"
#include "string.h"
#include "command_decoder.h"
#include "watch.h"
#include "timer_interrupts.h"


int main (){

	extern struct Watch sWatch;
	char cReceivedCommand [RECIEVER_SIZE];

	ServoInit(50);
	UART_InitWithInt(9600);
	Timer0Interrupts_Init(1000000, &WatchUpdate);

	
	while(1){
		
		if (Transmiter_GetStatus() == FREE){
			if(sWatch.fSeccondsValueChanged == 1){		
				sWatch.fSeccondsValueChanged=0;
				CopyString("sec ", cReceivedCommand);
				AppendUIntToString(sWatch.ucSecconds, cReceivedCommand);
				AppendString("\n", cReceivedCommand);
				Transmiter_SendString(cReceivedCommand);
			}
			if(sWatch.fMinutesValueChanged == 1){
				sWatch.fMinutesValueChanged=0;
				CopyString("min ", cReceivedCommand);
				AppendUIntToString(sWatch.ucMinutes, cReceivedCommand);
				AppendString("\n", cReceivedCommand);
				Transmiter_SendString(cReceivedCommand);
			}
		}
	}
}

