/*
 * Aplicacion.h
 *
 *  Created on: 14/06/2013
 *      Author: Marcelo
 */

#ifndef APLICACION_H_
#define APLICACION_H_

	#include "FW_GPIO.h"
	#include "KitInfo2_BaseBoard.h"
	#include "FW_UART0.h"
	#include "PR_UART0.h"
	#include "FW_UART1.h"
	#include "PR_UART1.h"
	#include "DR_Timers.h"
	#include "PR_Timers.h"

	#include "Teclado_4x1.h"
	#include "lcd.h"
	#include "Entradas.h"
	#include "Funciones.h"
	#include "PR_Relays.h"

	#define TOPE 200

	void InicializarKit ( void );
	void InicializacionSW (void);
	uint8_t upper (uint8_t c);
	uint8_t lower (uint8_t c);

#define IDLE 		0
#define R 			1
#define M 			2
#define C 			3
#define HORA		4
#define VALID		5
#define POSICION	6
#define VELOCIDAD	7


#endif /* APLICACION_H_ */
