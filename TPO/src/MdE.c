/*
 * MdE.c
 *
 *  Created on: 31 oct. 2018
 *      Author: max
 */

#include "Aplicacion.h"

volatile uint8_t flag2=0;
volatile uint8_t flag1=0;
volatile int estado=RESET;

void MdE (){

	static int FlagPuerta=0;
	static int flag2=0;
	volatile int Enrolamiento = TecladoHW();
	volatile int SPuerta = TecladoHW();
	volatile int Pulsador_al = TecladoHW();
	static int Pulsador = 0;
	static int Puerta = 0;
	//static int estado = RESET;
	//static uint8_t flag1=0;

	if (estado >= EMERGENCY)
		estado = RESET;

	switch(estado)
	{

		case RESET:

			IniHuella ();
			//TimerStart(Tespera,1,CambioE1,SEG);
			estado = NADA;
			//estado = STANDBY;
			break;

		case STANDBY:

			Recibir();

			if((HuellaDetectada() == TRUE) && flag1 && flag2==0)
			{
				flag1=0;

				PushLCD( 0x01 , LCD_CONTROL);

				IMG2TZ1();

				estado = VERIFIM2TZ1;
				//TimerStart(Tespera,1,CambioE2,SEG);
				//estado=NADA;

			}

			if((HuellaDetectada() == TRUE) && flag1 && flag2)
			{
				flag1=0;
				flag2=0;

				IMG2TZ2();

				estado = VERIFIM2TZ2;
				//TimerStart(Tespera,1,CambioE2,SEG);
				//estado=NADA;
			}

			if(HuellaDetectada() == 2 && flag1)
			{
				flag1=0;
				//TimerStart(Tsensor,1,IniHuella,SEG);
				IniHuella();
				estado=NADA;
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

		case VERIFIM2TZ1:

			Recibir();

			if(flag1 && VerifIMG2TZ() && Enrolamiento == 0xFF){
				flag1=0;
				IniBusqueda();
				//estado=BUSCANDO;
				TimerStart(Tespera,1,CambioE3,SEG);
				estado=NADA;

			}

			if(flag1 && VerifIMG2TZ() && Enrolamiento == ON){

				flag1=0;
				flag2=1;
				//TimerStart(Tespera,1,CambioE1,SEG);
				//STORE();
				//estado=NADA;

				IniHuella();
				//estado=NADA;
				estado=NADA;

			}

			break;

		case BUSCANDO:

			Recibir();

//
			if((flag1) && (VerifSEARCH()==TRUE))
			{
				flag1=0;
				char p[10];
				p[0]='B';
				p[1]='I';
				p[2]='E';
				p[3]='N';
				p[4]='V';
				p[5]='E';
				p[6]='N';
				p[7]='I';
				p[8]='D';
				p[9]='O';
				DisplayLCD(p,0,0);
				CERRADURA_ON;
				estado=ABIERTO;
				TimerStart(TPuerta,30,CambioE5,SEG);
				//IniHuella();
				//estado = STANDBY;
			}

			if((flag1) && (VerifSEARCH()==2)){
				flag1=0;
				char c[7];
				c[0]='U';
				c[1]='N';
				c[2]='K';
				c[3]='N';
				c[4]='O';
				c[5]='W';
				c[6]='N';
				DisplayLCD(c,0,0);
				IniHuella();
				estado = NADA;
			}
			break;

		case VERIFIM2TZ2:

			Recibir();

			if(flag1 && VerifIMG2TZ() && Enrolamiento == ON){

				flag1=0;
				REGMODEL();
				TimerStart(Tespera,1,CambioE6,SEG);
				estado=NADA;
			}

			break;

		case VERIFREGMODEL:

			Recibir();

			if(flag1 && VerifREGMODEL() && Enrolamiento == ON){

				flag1=0;
				STORE();
				//TimerStart(Tespera,1,CambioE4,SEG);
				estado=GUARDAR;
				//estado=NADA;

			}
			break;


		case GUARDAR:

			Recibir();

			if(flag1 && VerifSTORE() && Enrolamiento == ON){

				flag1=0;
				flag2=0;

				char f[13];

				f[0]='E';
				f[1]='N';
				f[2]='R';
				f[3]='O';
				f[4]='L';
				f[5]='A';
				f[6]='D';
				f[7]='O';
				f[8]=' ';
				f[9]=' ';
				f[10]=' ';
				f[11]=' ';
				f[12]=' ';

				DisplayLCD(f,0,0);

				//TimerStart(Tespera,2,CambioE1,SEG);

				IniHuella();

				estado=NADA;
			}
			break;

		case ALARMA:

			if((Pulsador_al==3) && (SPuerta==0xFF))
			{
				Alarma_OFF;
				IniHuella ();
				estado = NADA;

			}
			if((Pulsador_al==3) && (Puerta==2))
			{
				Alarma_OFF;
				estado = ABIERTO;

			}

			break;

		case ABIERTO:

			if(SPuerta==0xFF && FlagPuerta)
			{
				TimerStop(TPuerta);
				FlagPuerta=0;
				CERRADURA_OFF;
				IniHuella ();
				estado=NADA;
				//estado = REPOSO;

			}

			if(SPuerta==2)
				FlagPuerta=1;

			break;

		case NADA:
			break;

		default: estado = RESET;
	}



}
