/*
===============================================================================
 Name        : TPO-biblioteca-posta.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include "Aplicacion.h"
// TODO: insert other include files here

// TODO: insert other definitions and declarations here

extern volatile int dato;

int main(void) {

	InicializarKit();

	Tx();

    while(1) {

    	PopRx1(&dato);
    	bufferpop();
    	//TimerEvent();
    }
    return 0 ;
}
