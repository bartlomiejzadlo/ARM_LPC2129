#define NULL '\0'
#define TERMINATOR '\r'
#define RECIEVER_SIZE  20
#define TRANSMITER_SIZE  20

enum eRecieverStatus {EMPTY, READY, OVERFLOW};

struct RecieverBuffer{
	char cData[RECIEVER_SIZE];
	unsigned char ucCharCtr;
	enum eRecieverStatus eStatus;
};

enum eTransmiterStatus {FREE, BUSY};

struct TransmiterBuffer{
	char cData[TRANSMITER_SIZE];
	enum eTransmiterStatus eStatus;
	unsigned char fLastCharacter;
	unsigned char cCharCtr;
};




void UART_InitWithInt(unsigned int uiBaudRate);


char Transmiter_GetCharacterFromBuffer(void);
void Transmiter_SendString(char cString[]);
enum eTransmiterStatus Transmiter_GetStatus(void);

void Reciever_PutCharacterToBuffer(char cCharacter);
void Reciever_GetStringCopy(char * ucDestination);
enum eRecieverStatus eReciever_GetStatus(void);
