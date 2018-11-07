/*
 * Funciones.c
 *
 *  Created on: 7 nov. 2018
 *      Author: ignacio
 */
#include "Aplicacion.h"


void prueba(){


	TimerStart(1, 3 , ON_Relay ,SEG);
}

void ON_Relay (){

	int i;
	Relays(0, ON);

i++;
}
