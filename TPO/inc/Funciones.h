/*
 * Funciones.h
 *
 *  Created on: 31 oct. 2018
 *      Author: max
 */

#ifndef FUNCIONES_H_
#define FUNCIONES_H_



#endif /* FUNCIONES_H_ */

int Recibir(void);
void MdE (void);

void IniHuella (void);
void IniBusqueda(void);
int HuellaDetectada(void);
void IMG2TZ1(void);
void IMG2TZ2(void);
void REGMODEL(void);
void STORE(void);
int VerifSTORE (void);
int VerifREGMODEL (void);
int VerifIMG2TZ (void);
int VerifSEARCH(void);
void CambioE1(void); //STANDBY con IniHuella
void CambioE2(void); //STANDBY sin IniHuella
void CambioE3(void); //BUSCANDO
void CambioE4(void); //GUARDAR
void CambioE5(void); //ALARMA
void CambioE6(void);

