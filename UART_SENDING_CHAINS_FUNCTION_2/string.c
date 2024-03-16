#include "string.h"
#include "uart.h"

void CopyString(char pcSource[], char pcDestination[]){
	unsigned char ucLicznik;
	for(ucLicznik = 0; pcSource[ucLicznik]; ++ucLicznik){
		pcDestination[ucLicznik] = pcSource[ucLicznik];
	}
		pcDestination[ucLicznik] = pcSource[ucLicznik];
}


enum CompResult eCompareString(char pcStr1[], char pcStr2[]){
	
	unsigned char ucLicznik;
	
	for(ucLicznik = 0; pcStr1[ucLicznik]; ++ucLicznik){
		if( pcStr1[ucLicznik] != pcStr2[ucLicznik] ){
			return DIFFERENT;
		}
	}
	
	if( pcStr1[ucLicznik] != pcStr2[ucLicznik] ){
		return DIFFERENT;
	}
	
	return EQUAL;
	
}


enum Result eHexStringToUInt(char pcStr[],unsigned int *puiValue){
	
	unsigned char ucCharacterCounter;
	unsigned char ucCurrentCharacter;
	
	*puiValue=0;
	
	if((pcStr[0]!='0') || (pcStr[1]!='x') || (pcStr[2]==NULL)){
		return ERROR;
	}
	for(ucCharacterCounter=2; ucCharacterCounter<7; ucCharacterCounter++){
		ucCurrentCharacter = pcStr[ucCharacterCounter];
		if(ucCurrentCharacter==NULL){
			return OK;
		}
		else if(ucCharacterCounter==6){
			return ERROR;
		}
		*puiValue = *puiValue << 4;
		if(ucCurrentCharacter <= '9' && ucCurrentCharacter >= '0'){
			ucCurrentCharacter = ucCurrentCharacter-'0';
		}
		else if(ucCurrentCharacter <= 'F' && ucCurrentCharacter >= 'A'){
			ucCurrentCharacter = ucCurrentCharacter-'A'+10;
		}
		else{
			return ERROR;
		}
		*puiValue = (*puiValue) | ucCurrentCharacter;
	}
	return ERROR;
}


void ReplaceCharactersInString(char pcString[],char cOldChar,char cNewChar){
    unsigned char ucCharacterCounter;
    for(ucCharacterCounter = 0; pcString[ucCharacterCounter] != NULL; ucCharacterCounter++){
        if(pcString[ucCharacterCounter] == cOldChar){
            pcString[ucCharacterCounter] = cNewChar;
        }    
    }    
}

