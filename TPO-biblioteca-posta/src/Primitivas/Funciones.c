/*
 * Funciones.c
 *
 *  Created on: 7 nov. 2018
 *      Author: ignacio
 */
#include "Aplicacion.h"
volatile int dato;
void Tx(void);
void bufferpop(void);

void Tx (){

	char genimg[12];

	genimg[0] = 0xef;
	genimg[1] = 0x01;
	genimg[2] = 0xff;
	genimg[3] = 0xff;
	genimg[4] = 0xff;
	genimg[5] = 0xff;
	genimg[6] = 0x01;
	genimg[7] = 0x00;
	genimg[8] = 0x03;
	genimg[9] = 0x01;
	genimg[10] = 0x00;
	genimg[11] = 0x05;

	EnviarString1(genimg, 12);

}

void bufferpop(){

	int static i=0;
	uint8_t static datos[10];
	datos[i]=dato;
	i++;

}

