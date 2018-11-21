#include "Aplicacion.h"

extern volatile uint8_t trama[30];

extern volatile uint8_t FlagRecibir;

volatile uint8_t estadoRX = Header;

void AnalisisRX(){

	static uint8_t rx[1] = {0};

	static uint8_t i = 0;

	static volatile uint16_t Checksum = 0;

	static volatile uint16_t Suma = 0;

	if(PopRx1(rx) == 1)
		return;

	switch(estadoRX)
	{

		case Header:

			trama[i] = rx[0];

			i++;

			if(trama[0] == 0xef && trama[1] == 0x01 )
				estadoRX = ModuleAdress;


			break;

		case ModuleAdress:

			trama[i] = rx[0];

			i++;

			if(trama[2] == 0xff && trama[3] == 0xff && trama[4] == 0xff && trama[5] == 0xff)
				estadoRX = PackageIdent;

			else if(i==6){
				i=0;
				estadoRX = Header;
			}

			break;

		case PackageIdent:

			trama[i] = rx[0];

			i++;

			estadoRX = PackageLen;

			break;

		case PackageLen:

			 trama[i] = rx[0];

			 i++;

			 if(i == 9)
				 estadoRX = Restante;

			 break;

		case Restante:

			trama[i] = rx[0];

			i++;

			if(i==(trama[8] + 9)){

				Checksum |= trama[i-1];

				Checksum |= (trama[i-2] << 8);

				for(i=6;i<=trama[8]+6;i++)
					Suma += trama[i];

				if(Checksum == Suma){
					Checksum=0;
					Suma=0;
					FlagRecibir = 1;

				}

				estadoRX = Header;

				i = 0;
			}

			break;

	}
}
