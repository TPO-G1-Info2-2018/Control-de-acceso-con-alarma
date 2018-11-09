/*
 * FW_UART.c
 *
 *  Created on: 14/10/2013
 *      Author: marcelo
 */

#include "Aplicacion.h"



extern uint8_t buffer[TOPE];
extern uint8_t inx_out;
extern uint8_t inx_in;
extern uint8_t enviando;

uint8_t tx1Start;





void UART1_IRQHandler (void)
{
	uint8_t iir, dato;

	do
	{
		//IIR es reset por HW, una vez que lo lei se resetea.
		iir = U1IIR;

		if ( iir & 0x02 ) //THRE
		{
			if( !PopTx1(&dato) )
				U1THR = dato;
			else
				tx1Start = 0;
		}
		if ( iir & 0x04 ) //Data ready
		{
			PushRx1((uint8_t )U1RBR );
		}

	}
	while( ! ( iir & 0x01 ) ); /* me fijo si cuando entre a la ISR habia otra
						     	int. pendiente de atencion: b0=1 (ocurre unicamente si dentro del mismo
								espacio temporal lleguan dos interrupciones a la vez) */

}

void InitUART1 (void)
{
	//1.- Registro PCONP (0x400FC0C4) - bit 4 en 1 prende la UART1:
	PCONP |= 0x01<<4;
	//2.- Registro PCLKSEL0 (0x400FC1A8) - bits 8 y 9 en 0 seleccionan que el clk de la UART1 sea CCLK/4:
	PCLKSEL0 &= ~(0x03<<8);	//con un CCLK=100Mhz, nos queda PCLOCK=25Mhz
	//3.- Registro U1LCR (0x4001000C) - transmision de 8 bits, 1 bit de stop, sin paridad, sin break cond, DLAB = 1:
	U1LCR = 0x00000083;
	//4.- Registros U1DLL (0x40010000) y U1DLM (0x40010004) - 9600 baudios:
	U1DLM = 0;
	U1DLL = 0x1b;//0xA3 para 9600 0x1b para 57600
	//5.- Registros PINSEL0 (0x4002C000) y PINSEL1 (0x4002C004) - habilitan las funciones especiales de los pines:
	//TX1D : PIN ??	-> 		P0[15]	-> PINSEL0: 30:31
	SetPINSEL(TX1,PINSEL_FUNC1);
	//RX1D : PIN ??	-> 		P0[16]	-> PINSEL1: 00:01
	SetPINSEL(RX1,PINSEL_FUNC1);
	//6.- Registro U1LCR, pongo DLAB en 0:
	U1LCR = 0x03;
	//7. Habilito las interrupciones (En la UART -IER- y en el NVIC -ISER)
	U1IER = 0x03;
	ISER0 |= (1<<6);
}
