/*
 * PR_UART1.c
 *
 *  Created on: 7/9/2015
 *      Author: Gabriel
 */

#include "Aplicacion.h"


// Buffer de Transmision
uint8_t bufferTx1[TX1BUFFER_SIZE];
// Buffer de Recepcion
uint8_t bufferRx1[RX1BUFFER_SIZE];

// Indices de Transmision
uint8_t tx1_in,tx1_out;
// Indices de Recepcion
uint8_t rx1_in,rx1_out;
// Flags de estado de los buffers
uint8_t tx1_buffer_full = 0, tx1_buffer_empty = 1;
uint8_t rx1_buffer_full = 0, rx1_buffer_empty = 1;

extern uint8_t tx1Start;

uint8_t PushTx1(uint8_t dato)
{
	if(tx1_buffer_full)
		return 1;	//buffer lleno

	bufferTx1[tx1_in] = dato;
	tx1_in++;
	tx1_in %= TX1BUFFER_SIZE;
	tx1_buffer_empty = 0;	//si agrego un dato el buffer ya no esta vacio

	if(tx1_in == tx1_out)
		tx1_buffer_full = 1;	//se lleno el buffer

	if (tx1Start == 0)
	{
		tx1Start = 1;
		START_TX1();
	}
	return 0;	//dato agregado al buffer
}

uint8_t PopTx1( uint8_t *dato )
{
	if(tx1_buffer_empty)
		return 1;	//buffer vacio

	*dato = (uint8_t) bufferTx1[tx1_out];
	tx1_out++;
	tx1_out %= TX1BUFFER_SIZE;
	tx1_buffer_full = 0;	//si saco un dato el buffer ya no esta lleno

	if(tx1_out == tx1_in)
		tx1_buffer_empty = 1;	//se vacio el buffer

	return 0;	//dato sacado del buffer
}

uint8_t PushRx1( uint8_t dato )
{
	if(rx1_buffer_full)
		return 1;	//buffer lleno

	bufferRx1[rx1_in] = dato;
	rx1_in ++;
	rx1_in %= RX1BUFFER_SIZE;
	rx1_buffer_empty = 0;	//si agrego un dato el buffer ya no esta vacio

	if(rx1_in == rx1_out)
		rx1_buffer_full = 1;	//se lleno el buffer

	return 0;	//dato agregado al buffer
}

uint8_t PopRx1( uint8_t *dato )
{
	if(rx1_buffer_empty)
		return 1;	//buffer vacio

	*dato = (uint8_t) bufferRx1[rx1_out];
	rx1_out++;
	rx1_out %= RX1BUFFER_SIZE;
	rx1_buffer_full = 0;	//si saco un dato el buffer ya no esta lleno

	if(rx1_out == rx1_in)
		rx1_buffer_empty = 1;	//se vacio el buffer

	return 0;	//dato sacado del buffer
}

void EnviarString1 (const char *str)
{
	uint32_t i;
	for( i = 0 ; str[i] ; i++ )
		PushTx1( str[i] );
}

