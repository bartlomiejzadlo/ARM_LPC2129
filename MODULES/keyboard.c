#include <LPC21xx.H>
#include "keyboard.h"

#define BUT0_bm (1<<4)
#define BUT1_bm (1<<6)
#define BUT2_bm (1<<5)
#define BUT3_bm (1<<7)

enum KeyboardState eKeyboardRead(){
		if((IO0PIN&BUT0_bm)==0){
			return BUTTON_0;
		}
		if((IO0PIN&BUT1_bm)==0){
			return BUTTON_1;
		}
		if((IO0PIN&BUT2_bm)==0){
			return BUTTON_2;
		}
		if((IO0PIN&BUT3_bm)==0){
			return BUTTON_3;
		}
		else{
			return RELASED;
		}
}

void KeyboardInit(){
	IO0DIR =IO0DIR&(~(BUT0_bm|BUT1_bm|BUT2_bm|BUT3_bm));
}
