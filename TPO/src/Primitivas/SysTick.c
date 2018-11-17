
#include "Aplicacion.h"

extern volatile uint32_t delay;									//!< Variable de demora
extern volatile uint32_t delay2;								//!< Variable de demora 2


void InicializarSysTick ( void )
{
	STRELOAD = ( STCALIB / 4) - 1;
	STCURR = 0;

	CLKSOURCE = 1;
	ENABLE = 1;
	TICKINT = 1;
}



