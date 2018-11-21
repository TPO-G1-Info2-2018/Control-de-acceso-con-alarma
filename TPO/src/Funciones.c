/*
 * Funciones.c
 *
 *  Created on: 31 oct. 2018
 *      Author: max
 */

#include "Aplicacion.h"

extern volatile uint8_t FlagRecibir;

volatile uint8_t trama[30]={0};

extern volatile int estado;


void CambioE1(){

	IniHuella();

	estado=STANDBY;

}

void CambioE2(){

	char* a;

	a = "ALARMA";

	DisplayLCD(a,0,0);

	estado = ALARMA;

}

void IniHuella (){

	char static genimg[12];

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

void IniBusqueda(){

	char static search[17];

	search[0]=0xef;
	search[1]=0x01;
	search[2]=0xff;
	search[3]=0xff;
	search[4]=0xff;
	search[5]=0xff;
	search[6]=0x01;
	search[7]=0x00;
	search[8]=0x08;
	search[9]=0x1b;
	search[10]=0x01;
	search[11]=0x00;
	search[12]=0x00;
	search[13]=0x00;
	search[14]=0xa3;
	search[15]=0x00;
	search[16]=0xc8;

	EnviarString1(search, 17);

}


int Recibir(){

	static uint8_t rx[1] = {0};

	static uint8_t i = 0;

	if(PopRx1(rx) == 0 ){

		trama[i] = rx[0];

		i++;

		if(i==(trama[8]+9)){

			FlagRecibir = 1;

			i = 0;

		}

	}

	return 0;

}

void IMG2TZ2(){

	char Img2Tz2[13];

	Img2Tz2[0] = 0xef;
	Img2Tz2[1] = 0x01;
	Img2Tz2[2] = 0xff;
	Img2Tz2[3] = 0xff;
	Img2Tz2[4] = 0xff;
	Img2Tz2[5] = 0xff;
	Img2Tz2[6] = 0x01;
	Img2Tz2[7] = 0x00;
	Img2Tz2[8] = 0x04;
	Img2Tz2[9] = 0x02;
	Img2Tz2[10] = 0x02;
	Img2Tz2[11] = 0x00;
	Img2Tz2[12] = 0x09;

	EnviarString1(Img2Tz2, 13);

}

void REGMODEL(){

	char RegModel[12];

	RegModel[0] = 0xef;
	RegModel[1] = 0x01;
	RegModel[2] = 0xff;
	RegModel[3] = 0xff;
	RegModel[4] = 0xff;
	RegModel[5] = 0xff;
	RegModel[6] = 0x01;
	RegModel[7] = 0x00;
	RegModel[8] = 0x03;
	RegModel[9] = 0x05;
	RegModel[10] = 0x00;
	RegModel[11] = 0x09;

	EnviarString1(RegModel, 12);

}

void STORE(){

	char Store[15];

	static volatile char PageID = 0x01;

	Store[0] = 0xef;
	Store[1] = 0x01;
	Store[2] = 0xff;
	Store[3] = 0xff;
	Store[4] = 0xff;
	Store[5] = 0xff;
	Store[6] = 0x01;
	Store[7] = 0x00;
	Store[8] = 0x06;
	Store[9] = 0x06;
	Store[10] = 0x01;
	Store[11] = 0x00;
	Store[12] = PageID;
	Store[13] = 0x00;
	Store[14] = 0x0e + PageID;

	EnviarString1(Store, 15);

	PageID++;

}

void IMG2TZ1 (){

	char static Img2Tz1[13];

	Img2Tz1[0] = 0xef;
	Img2Tz1[1] = 0x01;
	Img2Tz1[2] = 0xff;
	Img2Tz1[3] = 0xff;
	Img2Tz1[4] = 0xff;
	Img2Tz1[5] = 0xff;
	Img2Tz1[6] = 0x01;
	Img2Tz1[7] = 0x00;
	Img2Tz1[8] = 0x04;
	Img2Tz1[9] = 0x02;
	Img2Tz1[10] = 0x01;
	Img2Tz1[11] = 0x00;
	Img2Tz1[12] = 0x08;

	EnviarString1(Img2Tz1, 13);

}

int VerificarTrama(){

	if(trama[9] == 0x00) //VALOR CORRECTO PARA TODOS LOS CASOS
		return 1;

	if(trama[9] == 0x09) //ERROR DE BUSQUEDA
			return 2;

	if(trama[9] == 0x02) //NO DETECTA DEDO
			return 3;

	return 0;

}

void DisplayDedo(){

	LimpiarLCD();

	char* d;

	d = "COLOQUE SU DEDO";

	DisplayLCD(d,0,0);

}

void LimpiarTrama(){

	int i=0;

	for(i=0;i<30;i++)
		trama[i]=0;
}
