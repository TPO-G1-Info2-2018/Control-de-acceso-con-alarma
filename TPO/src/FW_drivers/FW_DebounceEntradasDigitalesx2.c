/**
 	\file KitInfo2FW_Entradas.c
 	\brief Driver entradas digitales
 	\details Placa base
 	\author Ing. Marcelo Trujillo
 	\date 2012.04.25
*/

#include "Aplicacion.h"

volatile uint8_t BufferEntradas = 0;			//Buffer de Entradas Digitales

/**
	\fn void Debounce(void)
	\brief Filtrado de entradas digitales
 	\param void
	\return void
*/

void Debounce()
{
	uint8_t cambios,j = 0;
	uint8_t in = 0;

	static uint8_t ContadorEstados[ ENTRADAS ];

/*En 'j', almaceno el estado actual de las entradas. Un bit x cada entrada => 8
 * entradas para este ejemplo. Es aquí donde defino QUE bit de 'BufferEntradas'
 * corresponde a QUE entrada.*/
	j = GetPIN(IN2, ACTIVO_ALTO);
	if ( GetPIN(IN1, ACTIVO_BAJO) )
		j |= 0x02;
	if ( GetPIN(IN0, ACTIVO_BAJO) )	//enciende/apaga RGB Rojo y Azul
		j |= 0x04;
	if ( GetPIN(KEY0, ACTIVO_BAJO) )
		j |= 0x08;


	//----------------------

	cambios = ( BufferEntradas ^ j ); /*Si cambios vale 0 => no hubo cambios 
	respecto de todos los estados anteriores de todas las entradas. 
	Si cambios es distinto de cero => alguna entrada cambio de estado, con lo 
	que se procederá a su análisis-----*/

	if( cambios )	//Si el if es verdadero, es que hubo algún cambio=>analizo.
	{
		for( in = 0 ; in < ENTRADAS ; in++ )
		{
			if( cambios & (0x01 << in ) )
			{
				ContadorEstados[ in ] ++;

				if(ContadorEstados[ in ] == ACEPTAReSTADO)
				{
					ContadorEstados[ in ] = 0;
					BufferEntradas = BufferEntradas ^ (0x01 << in);
				}
			}
			else
				ContadorEstados[ in ] = 0;
		}
	}
	else	/*Si cambios vale cero puede ser por dos causas :
	a) Porque efectivamente las entradas estan estables y no se registraron 
		cambios de estados (lo mas probable)
	b) Porque las entradas que estaban siendo analizadas rebotaron y hacen 
		parecer que no hubo cambio de estados en ninguna. 
		Es poco probable que se dé con varias, entradas pero puede pasar.
		
	Si lo que paso es b) tengo que poner todos los contadores a cero, porque no
	sé cual rebotó. Si lo que paso fue a) y los pongo a cerobvno pasa nada.
	=> pongo los contadores a 0 en cualquiera de los dos casos*/
	{
		for( in = 0 ; in < ENTRADAS ; in++ )
			ContadorEstados[ in ] = 0;
	}
}
