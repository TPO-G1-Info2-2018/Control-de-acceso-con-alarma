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
void InicializarKit(void) {
	InicPLL();
	Inicializar_Teclado();
	Inicializar_Relay();
	Inicializar_RGB();
	Inicializar_LEDs();

	InicializarSysTick();
	InitLCD();

}

