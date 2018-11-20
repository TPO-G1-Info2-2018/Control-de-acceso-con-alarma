/*
 * Defines.h
 *
 *  Created on: 31 oct. 2018
 *      Author: max
 */

#ifndef DEFINES_H_
#define DEFINES_H_

#define Tsensor 1
#define Tespera 2
#define	TPuerta 3
#define Tlcd 4

#define TRUE 1
#define FALSE 0

#define RESET 0
#define STANDBY 1
#define GUARDAR 2
#define VERIFIM2TZ1 3
#define ABIERTO 4
#define ALARMA 5
#define BUSCANDO 6
#define NADA 7
#define VERIFIM2TZ2 8
#define VERIFREGMODEL 9
#define EMERGENCY 10


//#define Pulsador LeerED(ENTRADA0)
//#define Puerta LeerED(ENTRADA1)

//#define Enrolamiento LeerED(ENTRADA2)	//Cambiar para usar el qt

#define CERRADURA_ON Relays(RELAY0, ON)
#define CERRADURA_OFF Relays(RELAY0, OFF)

#define Alarma_ON BUZZER_ON
#define Alarma_OFF BUZZER_OFF

#endif /* DEFINES_H_ */
