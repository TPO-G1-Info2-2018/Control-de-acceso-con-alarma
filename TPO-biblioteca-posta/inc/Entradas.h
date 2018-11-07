/*
 * Entradas.h
 *
 *  Created on: 30/03/2013
 *      Author: Marcelo
 */

#ifndef ENTRADAS_H_
#define ENTRADAS_H_

/*---Aquí defino nombres de fantasía para identificar a cada uno de los bits de
 * 'BufferEntradas' que a su vez representan las entradas digitales del HW.
 * Qué bit corresponde a qué entrada queda definido en la función debounce()*/
	#define		UP	 			(   (BufferEntradas)      & 0x01 )
	#define		DOWN			( ( BufferEntradas >> 1 ) & 0x01 )
	#define		RGB_ROJO_AZUL	( ( BufferEntradas >> 2 ) & 0x01 )
	#define		KEY0_LED4		( ( BufferEntradas >> 3 ) & 0x01 )

	//--------------------------------------------------------------

	#define		ACEPTAReSTADO	10		//arbitrario
	#define		ENTRADAS		4		//cantidad de entradas a analizar

	/** -------------------------------------------------------------------------------------
	 * Prototipos
	 */
	void Debounce(void);

#endif /* ENTRADAS_H_ */
