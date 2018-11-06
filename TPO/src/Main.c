/*
 * Main.c
 *
 *  Created on: 31 oct. 2018
 *      Author: max
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include <bibliotecaInfoII.h>

#include "Funciones.h"


int main(void) {

	Inicializacion();

	UART1_Inicializacion (57600);

	Buzzer (OFF);

	while(1) {

		TimerEvent();
		MdE();

	}

	return 0;

}
