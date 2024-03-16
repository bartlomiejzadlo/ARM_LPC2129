#define MAX_TOKEN_NR 2
#define MAX_KEYWORD_STRING_LTH 10 
#define MAX_KEYWORD_NR 2

enum KeywordCode{
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


//extern struct Token asToken[MAX_TOKEN_NR];
extern struct Keyword asKeywordList[MAX_KEYWORD_NR];
extern unsigned char ucTokenNr;

void DecodeMsg(char *pcString);
