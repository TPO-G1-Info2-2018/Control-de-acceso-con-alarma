/*
 * Funciones.c
 *
 *  Created on: 31 oct. 2018
 *      Author: max
 */

#include "Aplicacion.h"

//extern uint8_t trama[20];
extern volatile uint8_t flag1;
volatile uint8_t trama[20]={0};


void IniHuella (){

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
	TimerStart(Tsensor,2,IniHuella,SEG);

}


int Recibir(){

	static uint8_t rx[1];
	static uint8_t i=0;

	if(PopRx1(rx) == 0){

		trama[i] = rx[0];
		if(i==trama[9]+9){
			i=0;
			flag1=1;
		}
		i++;
	}

	return 0;

}

int HuellaDetectada(){

	//static uint8_t rx[1];
	//static uint8_t i=0;
	//

	if(trama[11]==0x0a){

		return 1;

	}


    return 0;
}

void IM2TZ2(){

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

}

void IMG2TZ1 (){


	char Img2Tz1[13];


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

int VerifREGMODEL(){


	return 0;

}

int VerifIMG2TZ (){

	return 0;

}

int VerifSTORE () {


	return 0;
}
