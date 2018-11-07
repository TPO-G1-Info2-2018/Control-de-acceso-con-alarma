#include "Aplicacion.h"

extern volatile int DemoraLCD;

void SysTick_Handler(void)
{

// Aquí escribo todo aquello que deseo que ocurra cada 2,5ms.

	Debounce ();
	AnalizarTimers( );
	DriverTeclado();
	Dato_LCD();
	if ( Demora_LCD )
			Demora_LCD--;

}
