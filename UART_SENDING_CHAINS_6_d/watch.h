
struct Watch { 
	unsigned char ucMinutes; 
	unsigned char ucSecconds; 
	unsigned char fSeccondsValueChanged; 
	unsigned char fMinutesValueChanged;
};

void WatchUpdate(void);
