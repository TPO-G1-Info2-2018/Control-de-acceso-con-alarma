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

int main(void) {


    while(1) {
    	TimerEvent();

    	prueba();
    }
    return 0 ;
}
