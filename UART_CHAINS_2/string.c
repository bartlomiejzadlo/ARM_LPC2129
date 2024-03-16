#include "string.h"


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
