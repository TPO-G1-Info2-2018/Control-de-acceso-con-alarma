/*
 * PR_UART1.h
 *
 *  Created on: 7/9/2015
 *      Author: Gabriel
 */

#ifndef INC_PR_UART1_H_
#define INC_PR_UART1_H_

#include "Aplicacion.h""


#define TX1BUFFER_SIZE	100
#define RX1BUFFER_SIZE	100

uint8_t PushTx1(uint8_t dato);
uint8_t PopTx1( uint8_t *dato );
uint8_t PushRx1(uint8_t dato);
uint8_t PopRx1( uint8_t *dato );
void EnviarString1 (const char *str);



#endif /* INC_PR_UART1_H_ */
