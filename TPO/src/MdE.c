/*
 * MdE.c
 *
 *  Created on: 31 oct. 2018
 *      Author: max
 */

#include "Aplicacion.h"

volatile uint8_t FlagRecibir = 0;

volatile int estado = RESET;

extern volatile uint8_t BufferEntradas;

void MdE (){

	static int FlagPuerta = 0;

	static int FlagIMG2TZ1 = 0;

	volatile int Enrolamiento = TecladoHW();

	volatile int SPuerta = !(BufferEntradas & 0x01);

	volatile int Pulsador_al = Teclado();

	volatile int Pulsador_Apertura = Teclado();

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

			if(VerificarTrama() == TRUE && FlagRecibir == TRUE && FlagIMG2TZ1 == 0)
			{
				FlagRecibir = 0;

				LimpiarTrama();

				LimpiarLCD();

				IMG2TZ1();

				estado = VERIFIM2TZ1;

			}

			if(VerificarTrama() == TRUE && FlagRecibir == TRUE && FlagIMG2TZ1 == TRUE)
			{
				FlagRecibir = 0;

				FlagIMG2TZ1 = 0;

				LimpiarTrama();

				IMG2TZ2();

				estado = VERIFIM2TZ2;

			}

			if(VerificarTrama() == 3 && FlagRecibir == TRUE)
			{
				FlagRecibir = 0;

				LimpiarTrama();

				TimerStart(Tespera,1,CambioE1,SEG);

			}


			if(Pulsador_Apertura == 3)
			{
				TimerStop(Tespera);

				LimpiarLCD();

				CERRADURA_ON;

				estado = ABIERTO;

			}

			if(SPuerta == ON)
			{
				TimerStop(Tespera);

				LimpiarLCD();

				char* a;

				a = "ALARMA";

				DisplayLCD(a,0,0);

				Alarma_ON;

				estado = ALARMA;

			}

			break;


		case VERIFIM2TZ1:

			if(FlagRecibir == TRUE && VerificarTrama() == TRUE && Enrolamiento == NO_KEY)
			{
				FlagRecibir = 0;

				LimpiarTrama();

				IniBusqueda();

				estado=BUSCANDO;

			}

			if(FlagRecibir == TRUE && VerificarTrama() == TRUE && Enrolamiento == ON)
			{
				LimpiarLCD();

				LimpiarTrama();

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

			if(FlagRecibir == TRUE && VerificarTrama() == TRUE)
			{
				FlagRecibir = 0;

				LimpiarTrama();

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

				LimpiarTrama();

				char* c;

				c = "DESCONOCIDO";

				DisplayLCD(c,0,0);

				TimerStart(Tlcd,2,DisplayDedo,SEG);

				IniHuella();

				estado = STANDBY;

			}

			break;

		case VERIFIM2TZ2:

			if(FlagRecibir == TRUE && VerificarTrama() == TRUE && Enrolamiento == ON)
			{

				FlagRecibir = 0;

				LimpiarTrama();

				REGMODEL();

				estado=VERIFREGMODEL;
			}

			break;

		case VERIFREGMODEL:

			if(FlagRecibir == TRUE && VerificarTrama() == TRUE && Enrolamiento == ON)
			{

				FlagRecibir = 0;

				LimpiarTrama();

				STORE();

				estado = GUARDAR;

			}

			break;

		case GUARDAR:

			if(FlagRecibir == TRUE && VerificarTrama() == TRUE && Enrolamiento == ON)
			{
				FlagRecibir = 0;

				FlagIMG2TZ1 = 0;

				LimpiarTrama();

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

			if(Pulsador_al == 2 && SPuerta == OFF)
			{
				Alarma_OFF;

				LimpiarLCD();

				DisplayDedo();

				IniHuella ();

				estado = STANDBY;

			}

			if(Pulsador_al == 2 && SPuerta == ON)
			{
				Alarma_OFF;

				LimpiarLCD();

				estado = ABIERTO;

			}

			break;

		case ABIERTO:

			if(SPuerta == OFF && FlagPuerta == TRUE)
			{
				FlagPuerta = 0;

				LimpiarLCD();

				DisplayDedo();

				TimerStop(TPuerta);

				CERRADURA_OFF;

				IniHuella();

				estado = STANDBY;
			}

			if(SPuerta == ON)
				FlagPuerta = 1;

			break;

		case NADA:
			break;

		default: estado = RESET;
	}



}
