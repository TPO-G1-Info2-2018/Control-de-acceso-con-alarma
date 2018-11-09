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

#include "Aplicacion.h"


int main(void) {

	InicializarKit();

	while(1) {

		TimerEvent();
		MdE();

	}

	return 0;

}
