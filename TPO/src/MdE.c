/*
 * MdE.c
 *
 *  Created on: 31 oct. 2018
 *      Author: max
 */

#include "Aplicacion.h"

extern uint8_t rx[1];

void MdE (){

	static int Enrolamiento = 0;
	static int Pulsador = 0;
	static int Puerta = 0;
	static int estado = RESET;

	static uint8_t rx[1];

	PopRx1(rx);

	if (estado >= EMERGENCY)
		estado = RESET;

	switch(estado)
	{

		case RESET:

			IniHuella ();
			estado = STANDBY;
			break;

		case STANDBY:

			if((HuellaDetectada() == TRUE) && (Enrolamiento == OFF))
			{
				TimerStop(Tsensor);
				estado = VERIFICACION;

			}
			if((Pulsador == TRUE))
			{
				//CERRADURA_ON;
				estado = ABIERTO;

			}
			if((Puerta == TRUE))
			{
				//Alarma_ON;
				estado = ALARMA;

			}
			if((Enrolamiento == ON) && (HuellaDetectada() == TRUE))
			{
				IMG2TZ1();

			}

			break;

		case ENROLANDO:


//			if(VerifSTORE()==1)
//			{
//
//				IniHuella ();
//				estado = REPOSO;
//
//			}

			break;

		case VERIFICACION:

//			if((HuellaDetectada()==FALSE))
//			{
//				Huella=0();
//				IniHuella ();
//				estado = REPOSO;
//
//			}
//			if((Busqueda()==TRUE))
//			{
//				CERRADURA_ON();
//				estado = ABIERTO;
//
//			}

			break;

		case ALARMA:

//			if((Pulsador_al==TRUE) && (Puerta==False))
//			{
//				Alarma_OFF();
//				Huella=0;
//				IniHuella ();
//
//				estado = REPOSO;
//
//			}
//			if((Pulsador_al==TRUE) && (Puerta==TRUE))
//			{
//				Alarma_OFF();
//				estado = ABIERTO;
//
//			}

			break;

		case ABIERTO:

//			if((SPuerta==FALSE))
//			{
//				CERRADURA_OFF();
//				Huella=0;
//				IniHuella ();
//				estado = REPOSO;
//
//			}

			break;

		default: estado = RESET;
	}



}
