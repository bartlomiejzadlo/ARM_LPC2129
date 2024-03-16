#define NULL '\0'
#define TERMINATOR '\r'
#define RECIEVER_SIZE  10


enum eRecieverStatus {EMPTY, READY, OVERFLOW};

struct RecieverBuffer{
	char cData[RECIEVER_SIZE];
	unsigned char ucCharCtr;
	enum eRecieverStatus eStatus;
};


void UART_InitWithInt(unsigned int uiBaudRate);
void Reciever_PutCharacterToBuffer(char cCharacter);
void Reciever_GetStringCopy(char * ucDestination);
enum eRecieverStatus eReciever_GetStatus(void);
