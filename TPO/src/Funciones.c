/*
 * Funciones.c
 *
 *  Created on: 31 oct. 2018
 *      Author: max
 */


void Tx (){

    long genimg [3];

    genimg[0] = 0xffff01ef;
	genimg[1] = 0x0001ffff;
	genimg[2] = 0x05000103;

	Transmitir (UART1, genimg, 3 * sizeof(long));
	TimerStart (0, 1, Tx , SEG);

}

void IniHuella (){

    long genimg [3];

    genimg[0] = 0xffff01ef;
	genimg[1] = 0x0001ffff;
	genimg[2] = 0x05000103;

	Transmitir (UART1, genimg, 3 * sizeof(long));
	TimerStart (0, 1, Tx , SEG);

}


int HuellaDetectada(){

    int i = 0;
    int j = 0;

    static volatile int16_t rx = -1;

    volatile int16_t rxtext[8];

    for (j=0; j<7; j++){

    	rxtext[j]= -1;

    }

    switch (rx){

		case 0x00ef:
			rxtext[i] = rx;
			i++;
			break;

		case 0x0001:
			rxtext[i] = rx;
			i++;
			break;

		case 0x0007:
			rxtext[i] = rx;
			i++;
			break;

		case 0x0000:
			rxtext[i] = rx;
			i++;
			break;

		case 0x0003:
			rxtext[i] = rx;
			i++;
			break;

		case 0x0002:
			rxtext[i] = rx;
			i++;
			break;

		case 0x000c:
			rxtext[i] = rx;
			i = 0;
			if (rxtext[5] == 0x0000)
				return 1;
			break;

		case 0x000a:
			rxtext[i] = rx;
			i = 0;
			break;

		case 0x000b:
			rxtext[i] = rx;
			i = 0;
			break;

		case 0x000d:
			rxtext[i] = rx;
			i = 0;
			break;

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

	Transmitir (UART1, Img2Tz2, 13 * sizeof(char));

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

	Transmitir (UART1, RegModel, 12 * sizeof(char));

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

	Transmitir (UART1, Store, 15 * sizeof(char));

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

	Transmitir (UART1, Img2Tz1, 13 * sizeof(char));

}

int VerifREGMODEL(){

	volatile int16_t rxtext[8];

	static volatile int j=0;

	for (j=0; j<7; j++){

		rxtext[j]= -1;


	switch (rx){

		case 0x00ef:
			rxtext[i] = rx;
			i++;
			break;

		case 0x0001:
			rxtext[i] = rx;
			i++;
			break;

		case 0x0007:
			rxtext[i] = rx;
			i++;
			break;

		case 0x0000:
			rxtext[i] = rx;
			i++;
			break;

		case 0x0003:
			rxtext[i] = rx;
			i++;
			break;

		case 0x000a:
			rxtext[i] = rx;
			if(rxtext[5]==0x0000){
				i = 0;
				return 1;
			}
			i++;
			break;

		case 0x000b:
			rxtext[i] = rx;
			i = 0;
			break;

		case 0x0014:
			rxtext[i] = rx;
			i = 0;
			break;

	}


	return 0;

}

int VerifIMG2TZ (){

	volatile int16_t rxtext[8];

	static volatile int j=0;

	for (j=0; j<7; j++){

		rxtext[j]= -1;


	switch (rx){

			case 0x00ef:
				rxtext[i] = rx;
				i++;
				break;

			case 0x0001:
				rxtext[i] = rx;
				i++;
				break;

			case 0x0007:
				rxtext[i] = rx;
				i++;
				break;

			case 0x0000:
				rxtext[i] = rx;
				i++;
				break;

			case 0x0003:
				rxtext[i] = rx;
				i++;
				break;

			case 0x0015:
				rxtext[i] = rx;
				i++;
				break;

			case 0x0006:
				rxtext[i] = rx;
				i++;
				break;

			case 0x000a:
				rxtext[i] = rx;
				i = 0;
				if(rxtext[5]==0x0000)
					return 1;
				break;

			case 0x000b:
				rxtext[i] = rx;
				i = 0;
				break;

			case 0x0015:
				rxtext[i] = rx;
				i = 0;
				break;

			case 0x0022:
				rxtext[i] = rx;
				i = 0;
				break;
		}

		return 0;

}

int VerifSTORE () {

	volatile int16_t rxtext[8];

	static volatile int j=0;

	for (j=0; j<7; j++){

		rxtext[j]= -1;


	switch (rx){

			case 0x00ef:
				rxtext[i] = rx;
				i++;
				break;

			case 0x0001:
				rxtext[i] = rx;
				i++;
				break;

			case 0x0007:
				rxtext[i] = rx;
				i++;
				break;

			case 0x0000:
				rxtext[i] = rx;
				i++;
				break;

			case 0x0003:
				rxtext[i] = rx;
				i++;
				break;

			case 0x000b:
				rxtext[i] = rx;
				i++;
				break;

			case 0x0018:
				rxtext[i] = rx;
				i++;
				break;

			case 0x000a:
				rxtext[i] = rx;
				i = 0;
				if(rxtext[5]==0x0000)
					return 1;

				break;

			case 0x000b:
				rxtext[i] = rx;
				i = 0;
				break;

			case 0x0015:
				rxtext[i] = rx;
				i = 0;
				break;

			case 0x0022:
				rxtext[i] = rx;
				i = 0;
				break;
		}

		return 0;
}
