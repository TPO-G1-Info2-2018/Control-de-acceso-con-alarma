/*
 * SysTick.c
 *
 *  Created on: 26 ago. 2018
 *      Author: socco
 */
#include "Aplicacion.h"

extern volatile uint32_t delay;									//!< Variable de demora
extern volatile uint32_t delay2;								//!< Variable de demora 2

/** @fn void SysTickInic ( void )
 * @details Inicializacion del systick
 * @details No Portable
 * @param 	void
 * @return 	void.
 */
void InicializarSysTick ( void )
{
	STRELOAD = ( STCALIB / 4) - 1;
	STCURR = 0;

	CLKSOURCE = 1;
	ENABLE = 1;
	TICKINT = 1;
}



