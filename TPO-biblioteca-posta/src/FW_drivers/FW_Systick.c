#include "Aplicacion.h"



void SysTick_Handler(void)
{

// Aquí escribo todo aquello que deseo que ocurra cada 2,5ms.

	BarridoDisplay();
	AnalizarTimers( );

}
