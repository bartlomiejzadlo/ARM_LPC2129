#define NULL '\0'
#define TERMINATOR '\r'
#define RECIEVER_SIZE 4

void UART_InitWithInt(unsigned int uiBaudRate);
void Reciever_PutCharacterToBuffer(char cCharacter);
enum eRecieverStatus {EMPTY, READY, OVERFLOW};


struct RecieverBuffer{
	char cData[RECIEVER_SIZE];
	unsigned char ucCharCtr;
	enum eRecieverStatus eStatus;
};
