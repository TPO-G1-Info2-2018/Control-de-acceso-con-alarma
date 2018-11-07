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
	InicializarKit();

	Tx();

	InicializarKit();

	prueba();

    while(1) {
<<<<<<< HEAD
=======

    	TimerEvent();
>>>>>>> branch 'master' of https://github.com/TPO-G1-Info2-2018/Control-de-acceso-con-alarma.git

<<<<<<< HEAD
    	//TimerEvent();
=======



>>>>>>> branch 'master' of https://github.com/TPO-G1-Info2-2018/Control-de-acceso-con-alarma.git
    }
    return 0 ;
}
