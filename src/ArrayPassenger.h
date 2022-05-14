/*
 * passenger.h
 *
 *  Created on: 14 may. 2022
 *      Author: 54116
 */

#ifndef ARRAYPASSENGER_H_
#define ARRAYPASSENGER_H_

#define TAM_NAME 51
#define TAM_CODE 10

#define INACTIVO -1
#define DEMORADO 0
#define ACTIVO 1

#define TIPO_TURISTA 1
#define TIPO_PREMIUM 2
#define TIPO_EJECUTIVO 3

#define LIBRE 1
#define OCUPADO 0
#define BAJA -1

typedef struct{
	int id;
	char name[TAM_NAME];
	char lastname[TAM_NAME];
	float price;
	char flycode[TAM_CODE];
	int typePassenger;
	int statusflight;
	int isEmpty;
}ePassenger;

ePassenger eGen_CargarDatos(void);
int eGen_ObtenerIndexLibre(ePassenger array[], int TAM);
void eGen_MostrarUno(ePassenger Gen);
int eGen_hardcode(ePassenger* array, int limite, int indice, int id, char* nombre, char* apellido, float precio, char* codigo, int tipoPasajero,  int estado);
int eGen_Modificacion(ePassenger array[], int TAM);
ePassenger eGen_ModificarUno(ePassenger Gen);
int eGen_ObtenerID(void);
int calculoPrecio(ePassenger array[], int TAM);

int initPassengers(ePassenger* array, int limite);

int addPassengers(ePassenger array[], int TAM);

int removePassenger(ePassenger array[], int TAM);

int sortPassengers(ePassenger array[], int TAM, int criterio);

int printPassengers(ePassenger array[], int TAM);
int printPassengersActivos(ePassenger array[], int TAM);

int sortPassengersByCode(ePassenger array[], int TAM, int criterio);

int findPassengerById(ePassenger array[], int TAM, int ID);

#endif /* ARRAYPASSENGER_H_ */
