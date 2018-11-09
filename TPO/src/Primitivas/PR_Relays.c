/*
 * PR_Relays.c
 *
 *  Created on: 7 nov. 2018
 *      Author: max
 */

#include "Aplicacion.h"

void Relays(uint8_t nRelay , uint8_t estado){

	switch (nRelay){

		case 0:

			SetPIN(LED1 , estado );
			break;

		case 1:

			SetPIN(LED2 , estado );
			break;

		case 2:

			SetPIN(LED3 , estado );
			break;

		case 3:

			SetPIN(LED4 , estado );
			break;

	}




}
