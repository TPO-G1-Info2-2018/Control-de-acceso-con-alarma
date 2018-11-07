/*
 * KitInic.c
 */

#include "RegsLPC1769.h"
#include "KitInfo2_BaseBoard.h"
#include "FW_GPIO.h"
#include "Oscilador.h"
#include "Aplicacion.h"



//-----------------------------------------------------------------------------
// Inicialización general del Kit de acuerdo al uso que se le dará.
//-----------------------------------------------------------------------------
void InicializarKit ( void )
{
	InicPLL();
	Inicializar_RGB();
	InitUART0();
	InitUART1();
	Inicializar_LEDXpresso();

}

