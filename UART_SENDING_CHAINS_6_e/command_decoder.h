#define MAX_TOKEN_NR 5
#define MAX_KEYWORD_STRING_LTH 10 
#define MAX_KEYWORD_NR 5

enum KeywordCode{
	CALC,
	ID,
	GOTO,
	CALLIBRATION,
};

union TokenValue{
	enum KeywordCode eKeyword;
	unsigned int uiNumber;
	char* pcString;
};

enum TokenType{
	KEYWORD, 
	NUMBER, 
	STRING
};

struct Token{
	enum TokenType eType;
	union TokenValue uValue;
};


struct Keyword{
	enum KeywordCode eCode;
	char cString[MAX_KEYWORD_STRING_LTH + 1];
};


void DecodeMsg(char *pcString);
