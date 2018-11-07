/*******************************************************************************************************************************//**
 *
 * @file		PR_lcd.h
 * @brief		DESCRIPCION ------------------------
 * @date		25/10/2017
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef SOURCES_PRIMITIVAS_H_PR_LCD_H_
#define SOURCES_PRIMITIVAS_H_PR_LCD_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "DR_tipos.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/
#define		LCD_Clear()		LCD_Push( 0x01 , LCD_CONTROL )

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void LCD_Display(const char *string, uint8_t line ,uint8_t pos);

#endif /* SOURCES_PRIMITIVAS_H_PR_LCD_H_ */