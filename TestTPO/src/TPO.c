/*
===============================================================================
 Name        : TPO.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif


#include <bibliotecaInfoII.h>

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

void Tx (void);

void Tx (){

    long genimg [3];

    genimg[0] = 0xffff01ef;
	genimg[1] = 0x0001ffff;
	genimg[2] = 0x05000103;

	Transmitir (UART1, genimg, 3 * sizeof(long));
	TimerStart (0, 1, Tx , SEG);

}

int main(void) {

    // TODO: insert code here

	Inicializacion();

//	UART0_Inicializacion (9600);
	UART1_Inicializacion (57600);

    // Force the counter to be placed into memory
    static volatile int i = 0 ;

    int j;

    long genimg [3];

    static volatile int16_t rx = -1;

    static volatile int16_t rxtext[12];

    for (j=0; j<11; j++){

    	rxtext[j]= -1;

    }


    genimg[0] = 0xffff01ef;
	genimg[1] = 0x0001ffff;
	genimg[2] = 0x05000103;

    // Enter an infinite loop, just incrementing a counter

	Buzzer (OFF);


	Transmitir (UART1, genimg, 3 * sizeof(long));
//	TimerStart (0, 1, Tx , SEG);

	while(1) {

//		TimerEvent();
	rx = UART1_PopRX();

		if(rx != -1){
			rxtext[i] = rx;
//			i++;
//			if(i==13)
//				i=0;
		}

//		switch (rx){
//
//			case 0x00ef:
//				rxtext[i] = rx;
//				i++;
//				break;
//
//			case 0x0001:
//				rxtext[i] = rx;
//				i++;
//				break;
//
//			case 0x0007:
//				rxtext[i] = rx;
//				i++;
//				break;
//
//			case 0x0000:
//				rxtext[i] = rx;
//				i++;
//				break;
//
//			case 0x0003:
//				rxtext[i] = rx;
//				i++;
//				break;
//
//			case 0x0002:
//				rxtext[i] = rx;
//				i++;
//				break;
//
//			case 0x000c:
//				rxtext[i] = rx;
//				i = 0;
//				break;
//
//		}

//		if (rxtext[9] == 0x0000)
//			TimerStop(0);

    }

    return 0 ;
}
