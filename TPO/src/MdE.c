/*
 * MdE.c
 *
 *  Created on: 31 oct. 2018
 *      Author: max
 */

#include "Aplicacion.h"

volatile uint8_t FlagRecibir=0;

volatile int estado=RESET;

void MdE (){

	static int FlagPuerta = 0;

	static int FlagIMG2TZ1 = 0;

	volatile int Enrolamiento = TecladoHW();

	volatile int SPuerta = TecladoHW();

	volatile int Pulsador_al = TecladoHW();

	volatile int Pulsador_Apertura = TecladoHW();

	if (estado >= EMERGENCY)
		estado = RESET;

	switch(estado)
	{

		case RESET:

			IniHuella();

			DisplayDedo();

			estado = STANDBY;

			break;

		case STANDBY:

			Recibir();

			if(VerificarTrama() == TRUE && FlagRecibir == TRUE && FlagIMG2TZ1 == 0)
			{
				FlagRecibir = 0;

				LimpiarLCD();

				IMG2TZ1();

				estado = VERIFIM2TZ1;

			}

			if(VerificarTrama() == TRUE && FlagRecibir == TRUE && FlagIMG2TZ1 == TRUE)
			{
				FlagRecibir = 0;

				FlagIMG2TZ1 = 0;

				IMG2TZ2();

				estado = VERIFIM2TZ2;

			}

			if(VerificarTrama() == 3 && FlagRecibir == TRUE)
			{
				FlagRecibir = 0;

				TimerStart(Tespera,1,CambioE1,SEG);

			}


			if(Pulsador_Apertura == 4)
			{
				LimpiarLCD();

				CERRADURA_ON;

				estado = ABIERTO;

			}

			if(SPuerta == 2)
			{
				LimpiarLCD();

				char* a;

				a = "ALARMA";

				DisplayLCD(a,0,0);

				Alarma_ON;

				estado = ALARMA;

			}

			break;


		case VERIFIM2TZ1:

			Recibir();

			if(FlagRecibir == TRUE && VerificarTrama() == TRUE && Enrolamiento == 0xFF)
			{
				FlagRecibir = 0;

				IniBusqueda();

				estado=BUSCANDO;

			}

			if(FlagRecibir == TRUE && VerificarTrama() == TRUE && Enrolamiento == ON)
			{
				LimpiarLCD();

				char* b;

				char* c;

				b = "COLOQUELO";

				c = "NUEVAMENTE";

				DisplayLCD(b,0,0);

				DisplayLCD(c,1,0);

				FlagRecibir = 0;

				FlagIMG2TZ1 = 1;

				IniHuella();

				estado=STANDBY;

			}

			break;

		case BUSCANDO:

			Recibir();

			if(FlagRecibir == TRUE && VerificarTrama() == TRUE)
			{
				FlagRecibir = 0;

				char* p;

				p = "BIENVENIDO";

				DisplayLCD(p,0,0);

				CERRADURA_ON;

				estado = ABIERTO;

				TimerStart(TPuerta,30,CambioE2,SEG);

			}

			if(FlagRecibir == TRUE && VerificarTrama() == 2)
			{
				FlagRecibir = 0;

				char* c;

				c = "DESCONOCIDO";

				DisplayLCD(c,0,0);

				TimerStart(Tlcd,2,DisplayDedo,SEG);

				IniHuella();

				estado = STANDBY;

			}

			break;

		case VERIFIM2TZ2:

			Recibir();

			if(FlagRecibir == TRUE && VerificarTrama() == TRUE && Enrolamiento == ON)
			{

				FlagRecibir = 0;

				REGMODEL();

				estado=VERIFREGMODEL;
			}

			break;

		case VERIFREGMODEL:

			Recibir();

			if(FlagRecibir == TRUE && VerificarTrama() == TRUE && Enrolamiento == ON)
			{

				FlagRecibir = 0;

				STORE();

				estado = GUARDAR;

			}

			break;

		case GUARDAR:

			Recibir();

			if(FlagRecibir == TRUE && VerificarTrama() == TRUE && Enrolamiento == ON)
			{
				FlagRecibir = 0;

				FlagIMG2TZ1 = 0;

				LimpiarLCD();

				char* f;

				f = "ENROLADO";

				DisplayLCD(f,0,0);

				TimerStart(Tlcd,2,DisplayDedo,SEG);

				IniHuella();

				estado = STANDBY;
			}

			break;

		case ALARMA:

			if(Pulsador_al == 5 && SPuerta == 0xFF)
			{
				Alarma_OFF;

				LimpiarLCD();

				DisplayDedo();

				IniHuella ();

				estado = STANDBY;

			}

			if(Pulsador_al == 5 && SPuerta == 2)
			{
				Alarma_OFF;

				LimpiarLCD();

				estado = ABIERTO;

			}

			break;

		case ABIERTO:

			if(SPuerta == 0xFF && FlagPuerta == TRUE)
			{
				FlagPuerta = 0;

				LimpiarLCD();

				DisplayDedo();

				TimerStop(TPuerta);

				CERRADURA_OFF;

				IniHuella();

				estado = STANDBY;
			}

			if(SPuerta == 2)
				FlagPuerta = 1;

			break;

		case NADA:
			break;

		default: estado = RESET;
	}



}
