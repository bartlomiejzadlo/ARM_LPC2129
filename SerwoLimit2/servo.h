void ServoInit(unsigned int uiServoFrequency);
void ServoCallib(void);
void ServoGoTo(unsigned int uiPosition);

void DetectorInit(void);
enum DetectorState eReadDetector(void);
void Automat(void);

enum DetectorState {ACTIVE, INACTIVE};
enum ServoState {CALLIB, IDLE, IN_PROGRESS, SERWO_LIMIT};

struct Servo{
	enum ServoState eState; 
	unsigned int uiCurrentPosition; 
	unsigned int uiDesiredPosition;
};
