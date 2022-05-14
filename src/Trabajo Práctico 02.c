/*
 ============================================================================
 Name        : Trabajo.c
 Author      : Mauro Servin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "ArrayPassenger.h"
#include "miBiblioteca.h"

#define CANT_PASAJEROS 2000

int main(void) {
	setbuf(stdout, NULL);

	int opcion;
	int respuesta;

	ePassenger arrayPasajeros[CANT_PASAJEROS];
	initPassengers(arrayPasajeros, CANT_PASAJEROS);
	eGen_hardcode(arrayPasajeros, CANT_PASAJEROS, 0, eGen_ObtenerID(), "JUAN", "ALVAREZ", 200, "C3F", TIPO_TURISTA, ACTIVO);
	eGen_hardcode(arrayPasajeros, CANT_PASAJEROS, 1, eGen_ObtenerID(), "MIGUEL", "CARRANZA", 1000, "B2L", TIPO_PREMIUM, DEMORADO);
	eGen_hardcode(arrayPasajeros, CANT_PASAJEROS, 2, eGen_ObtenerID(), "NAHUEL", "BERUTTI", 750, "T3R", TIPO_EJECUTIVO, ACTIVO);

	do{
	respuesta = utn_getNumero(&opcion, "\n1) ALTA DE PASAJEROS. \n2) MODIFICAR DATOS DE PASAJERO. \n3) BAJA DE PASAJERO. \n4) INFORME.", "\nERROR. OPCIÓN INVÁLIDA", 0, 4, 2);

	if(respuesta == 0){
		switch(opcion){
		case 0:
		break;

		case 1:
			addPassengers(arrayPasajeros, CANT_PASAJEROS);
		break;

		case 2:
			eGen_Modificacion(arrayPasajeros, CANT_PASAJEROS);
			printPassengers(arrayPasajeros, CANT_PASAJEROS);
		break;

		case 3:
			removePassenger(arrayPasajeros, CANT_PASAJEROS);
			printPassengers(arrayPasajeros, CANT_PASAJEROS);
		break;

		case 4:
			respuesta = utn_getNumero(&opcion, "\n1) Listado de los pasajeros ordenados alfabéticamente por Apellido y Tipo de pasajero. "
					"\n2) Total y promedio de los precios de los pasajes, y cuántos pasajeros superan el precio promedio. "
					"\n3) Listado de los pasajeros por Código de vuelo y estados de vuelos ‘ACTIVO’.", "\nERROR. OPCIÓN INVÁLIDA", 1, 3, 2);

			switch(opcion){
			case 1:
				sortPassengers(arrayPasajeros, CANT_PASAJEROS, -1);
				printPassengers(arrayPasajeros, CANT_PASAJEROS);
			break;

			case 2:
				calculoPrecio(arrayPasajeros, CANT_PASAJEROS);
			break;

			case 3:
				sortPassengersByCode(arrayPasajeros, CANT_PASAJEROS, -1);
				printPassengersActivos(arrayPasajeros, CANT_PASAJEROS);
			break;
			}
		break;
		}
	}
	}while(opcion != 0);


	return EXIT_SUCCESS;
}
