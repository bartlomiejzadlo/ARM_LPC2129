#include "watch.h"

struct Watch sWatch;

void WatchUpdate(){
	sWatch.ucSecconds++;
	sWatch.fSeccondsValueChanged = 1;
	if(sWatch.ucSecconds == 60){
		sWatch.ucSecconds = 0;
		sWatch.ucMinutes++;
		sWatch.fMinutesValueChanged = 1;
	}
	if(sWatch.ucMinutes == 60){
		sWatch.ucMinutes = 0;
	}
}
