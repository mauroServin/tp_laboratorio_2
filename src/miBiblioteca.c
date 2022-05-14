/*
 * miBiblioteca.c
 *
 *  Created on: 14 may. 2022
 *      Author: 54116
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "miBiblioteca.h"

static int utn_getInt(int* pResultado);
static int utn_esNumerica(char* cadena, int limite);
static int utn_GetFloat(float* pResultado);
static int utn_esFlotante(char* cadena);
static int utn_getString(char* cadena, int longitud);
static int getNombre(char* pResultado, int longitud);
static int utn_esNombre(char* cadena, int longitud);
static int utn_esDescripcion(char* cadena, int longitud);
static int getDescripcion(char* pResultado, int longitud);


int utn_getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos){
	int retorno = -1;
	int bufferInt;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0)
	{
		do{
			printf("%s", mensaje);

			if(utn_getInt(&bufferInt) == 0 && bufferInt >= minimo && bufferInt <= maximo)
			{
				*pResultado = bufferInt;
				retorno = 0;
				break;
			}
			else
			{
				printf("%s", mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);

	}

	return retorno;
}


int utn_getNumeroFlotante(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos){
	int retorno = -1;
	float buffer;

	if (pResultado != NULL && mensaje != NULL && mensajeError != NULL
			&& minimo <= maximo && reintentos >= 0) {
		while (reintentos >= 0) {
			reintentos--;
			printf("%s", mensaje);

			if (utn_GetFloat(&buffer) == 0) {
				if (buffer >= minimo && buffer <= maximo) {
					*pResultado = buffer;
					retorno = 0;
					break;
				}
			}
			printf("%s", mensajeError);
		}
	}

	return retorno;
}


int utn_getCaracter(char* pResultado, char* mensaje, char* mensajeError, char minimo, char maximo, int reintentos){
	int retorno = -1;
	char buffer;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0)
	{
		do{
			printf("%s", mensaje);
			scanf("%c", &buffer);
			if(buffer >= minimo && buffer <= maximo)
			{
				*pResultado = buffer;
				retorno = 0;
			}
			else
			{
				printf("%s", mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);

	}

	return retorno;
}


int utn_printArrayInt(int* pArray, int limite){
	int retorno;

	if(pArray != NULL){
		if(limite >= 0){
			for(int i = 0; i < limite; i++){
				printf("[DEBUG] INDICE: %d -- VALOR: %d\n", i, pArray[i]);
			}
		}else{
			retorno = -2;// EL LIMITE ES NEGATIVO
		}
	}else{
		retorno = -1;//EL PUNTERO ES NULO
	}

	return retorno;
}


int utn_ordenarArrayInt(int* pArray, int limite){
	int retorno;
	int flagSwap;
	int contador;
	int buffer;
	int nuevoLimite = limite-1;

	if(pArray != NULL){
		if(limite >= 0){
			do{
				flagSwap = 0;
				for(int i = 0; i < limite - nuevoLimite; i++){
					contador++;
					if(pArray [i] < pArray[i+1]){/*CAMBIANDO EL MENOR A MAYOR PERMITE
						CAMBIAR EL ORDENAMIENTO*/
						flagSwap = 1;
						buffer = pArray[i];
						pArray[i] = pArray[i+1];
						pArray[i+1] = buffer;
					}
					nuevoLimite--;
				}
			}while(flagSwap);

		}else{
			retorno = -2;
			puts("El limite es negativo");
		}
	}else{
		retorno = -1;
		puts("El puntero es nulo");
	}

	retorno = contador;

	return retorno;
}


void utn_menu(){
	int opcion;
	int respuesta;

	respuesta = utn_getNumero(&opcion, "Prueba de menu", "Error", 1, 10, 3);

	do{
		if(!respuesta){
			switch(opcion){
			case 1:
				puts("Entre al caso 1.\n");
			break;

			case 2:
				puts("Entre al caso 2.\n");
			break;
			}
		}
	}while(opcion != 3);
}


static int utn_getInt(int* pResultado){
	int retorno = -1;
	char bufferString[50];

	if(pResultado != NULL){
		if(utn_myGets(bufferString, sizeof(bufferString)) == 0){
			if(utn_esNumerica(bufferString, sizeof(bufferString))){
				retorno = 0;
				*pResultado = atoi(bufferString);
			}
		}
	}

	return retorno;
}


static int utn_esNumerica(char* cadena, int limite){
	int retorno = -1; // 1= ERROR

	if (cadena != NULL && limite > 0) {
		retorno = 1; // 1 = VERDADERO
		for (int i = 0; i < limite && cadena[i] != '\0'; i++) {
			if (i == 0 && (cadena[i] == '+' || cadena[i] == '-')) {
				continue;
			}
			if (cadena[i] > '9' || cadena[i] < '0') {
				retorno = 0; // 0 = FALSO
				break;
			}
		}
	}

	return retorno;
}


static int utn_GetFloat(float* pResultado){
	int retorno = -1;
	char buffer[64];

	fflush(stdin);

	if(pResultado != NULL){
		if (utn_myGets(buffer, sizeof(buffer)) == 0 && utn_esFlotante(buffer)) {
			retorno = 0;
			*pResultado = atof(buffer); //CONVIERTE UN STRING EN UN FLOTANTE
		}

	}

	return retorno;
}


static int utn_esFlotante(char* cadena){
	int retorno = 1;
	int i;
	int contadorPuntos = 0;

	if(cadena != NULL && strlen(cadena) > 0){
		for(i = 0; cadena[i] != '\0'; i++){
			if(i == 0 && (cadena[i] == '-' || cadena[i] == '+')){
				continue;
			}
			if(cadena[i] < '0' || cadena[i] > '9'){
				if(cadena[i] == '.' && contadorPuntos == 0)
				{
					contadorPuntos ++;

				}else{
					retorno = 0;
					break;
				}
			}
		}
	}

	return retorno;
}


int utn_myGets(char* cadena, int longitud){

	int retorno = -1;
	char bufferString[4096]; //ESTÁ MAL, SE SOLUCIONA CON MEMORIA DINAMICA

	if(cadena != NULL && longitud > 0){
		fflush(stdin);
		if(fgets(bufferString, sizeof(bufferString), stdin) != NULL){
			if(bufferString[strnlen(bufferString, sizeof(bufferString))-1] == '\n'){
				bufferString[strnlen(bufferString, sizeof(bufferString))-1] = '\0';
			}
			if(strnlen(bufferString, sizeof(bufferString)) <= longitud){
				strncpy(cadena, bufferString, longitud);
				retorno = 0;
			}
		}
	}
	return retorno;
}


int utn_initArrayFlotante(float* pArray, int longitud, float valorInicial){
	int retorno = -1;

	if(pArray != NULL){
		if(longitud >= 0){
			for(int i = 0; i < longitud; i++){
				pArray[i] = valorInicial;
			}

			retorno = 0;
		}
	}

	return retorno;
}


int utn_printArrayFlotante(float* pArray, int longitud){
	int retorno = -1;

	if(pArray != NULL && longitud > 0){
		retorno = 0;
		for(int i = 0; i < longitud; i++){
			printf(" \n INDICE: [%d] --- DIA: [%d] --- VALOR: %.2f", i, i+1, pArray[i]);
		}
	}

	return retorno;
}


int ordenarNumeros(int* pArray, int limite){
	int retorno = -1;
	int flagSwap;
	int buffer;

	if(pArray != NULL && limite > 0){
		do{
			flagSwap = 0;
			for(int i = 0; i < limite-1; i++){
				if(pArray[i] > pArray[i+1]){
					buffer = pArray[i];
					pArray[i] = pArray[i+1];
					pArray[i+1] = buffer;
					flagSwap = 1;
				}
			}
		}while(flagSwap);

		retorno = 0;
	}
	return retorno;
}


int cargarTemperaturas(float* pArray, int longitud){
	int retorno = -1;
	int dia;
	int respuesta;
	float temperatura;

	if(pArray != NULL && longitud > 0){
		retorno  = 0;
		respuesta = utn_getNumero(&dia, "\n Que día desea modificar?:", "\n Dia inválido [1-31]", 1, 31, 2);

		if(!respuesta){

			respuesta = utn_getNumeroFlotante(&temperatura, "Ingrese la temperatura:", "Error, temperatura fuera de rango.", -50, 70, 2);
			if(!respuesta){
				pArray[dia-1] = temperatura;
			}
		}
	}
	return retorno;
}


int imprimirNumeros(int* pArray, int limite){
	int retorno;
	if(pArray!= NULL && limite > 0){
		for(int i = 0; i < limite; i++){
			printf("\nINDICE: [%d] --- VALOR: %d", i, pArray[i]);
		}
		retorno = 0;
	}
	return retorno;
}


int solicitarNumeros(int* pArray, int limite){
	int retorno;
	if(pArray!= NULL && limite > 0){
		retorno = 0;
		for(int i = 0; i < limite; i++){
			if(utn_getNumero(&pArray[i], "\nIngrese un numero entero:", "Error.", -1000, 1000, 2) == -1){
				retorno = -1;
				break;
			}
		}
	}
	return retorno;
}


int borrarImpares(int* pArray, int limite){
	int retorno = -1;

	if(pArray != NULL && limite > 0){
		for(int i = 0; i< limite; i++){
			if((pArray[i] % 2) != 0){
				pArray[i] = 0;
			}
		}
		retorno = 0;
	}

	return retorno;
}


int utn_contarPalabras(char cadena[], int len, int* pPalabras){
	int retorno = -1;
	int contador = 0;

	if(pPalabras != NULL && cadena != NULL && len > 0){
		retorno = 0;
		for(int i = 0; i < len && cadena[i] != '\0'; i++){
			if(cadena[i] == ' '){
				contador++;
			}
		}
		*pPalabras = contador;
	}
	return retorno;
}


static int utn_getString(char *cadena, int longitud) {
	int retorno = -1;
	char bufferString[4096];

	if (cadena != NULL && longitud > 0) {
		fflush(stdin);
		if (fgets(bufferString, sizeof(bufferString), stdin) != NULL) {
			if (bufferString[strnlen(bufferString, sizeof(bufferString)) - 1]
					== '\n') {
				bufferString[strnlen(bufferString, sizeof(bufferString)) - 1] =
						'\0';
			}
			if (strnlen(bufferString, sizeof(bufferString)) <= longitud) {
				strncpy(cadena, bufferString, longitud);
				retorno = 0;
			}
		}
	}

	return retorno;
}


static int getNombre(char* pResultado, int longitud){
	int retorno = -1;
	char buffer[4096];

	if(pResultado != NULL){
		if(utn_getString(buffer, sizeof(buffer)) == 0 && utn_esNombre(buffer, sizeof(buffer)) == 0 && strnlen(buffer, sizeof(buffer)) < longitud){
			strncpy(pResultado, buffer, longitud);
			retorno = 0;
		}
	}
	return retorno;
}


static int utn_esNombre(char* cadena, int longitud){
	int retorno = 1;

	if(cadena != NULL && longitud > 0){
		for(int i = 0; i < longitud; i++){
			if((cadena[i] < 'A' || cadena[i] > 'Z') && (cadena[i] < 'a' || cadena[i] > 'z')){
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}


int utn_getNombre(char* pResultado, int longitud, char* mensaje, char* mensajeError, int reintentos){
	char bufferString[4096];
	int retorno = -1;

	while(reintentos >= 0) {
		reintentos--;
		printf("%s", mensaje);
		if(getNombre(bufferString, sizeof(bufferString)) == 0 && strnlen(bufferString, sizeof(bufferString)) < longitud) {
			strncpy(pResultado, bufferString, longitud);
			retorno = 0;
			break;
		}
		printf("%s", mensajeError);
	}
	return retorno;
}


static int getDescripcion(char* pResultado, int longitud){
	int retorno = -1;
	char buffer[4096];

	if(pResultado != NULL){
		if(utn_getString(buffer, sizeof(buffer)) == 0 && utn_esDescripcion(buffer, sizeof(buffer)) && strnlen(buffer, sizeof(buffer)) < longitud){
			strncpy(pResultado, buffer, longitud);
			retorno = 0;
		}
	}
	return retorno;
}


static int utn_esDescripcion(char* cadena, int longitud){
	int retorno = 1;

	if(cadena != NULL && longitud > 0){
		for(int i = 0; cadena[i] != '\0' && i < longitud; i++){
			if((cadena[i] != '.' && cadena[i] != ' ') && (cadena[i] < 'A' || cadena[i] > 'Z') && (cadena[i] < 'a' || cadena[i] > 'z') && (cadena[i] < '0' || cadena[i] > '9')){
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}


int utn_getDescripcion(char* pResultado, int longitud, char* mensaje, char* mensajeError, int reintentos){
	char bufferString[4096];
	int retorno = -1;

	while(reintentos >= 0) {
		reintentos--;
		printf("%s", mensaje);
		if(getDescripcion(bufferString, sizeof(bufferString)) == 0 && strnlen(bufferString, sizeof(bufferString)) < longitud) {
			strncpy(pResultado, bufferString, longitud);
			retorno = 0;
			break;
		}
		printf("%s", mensajeError);
	}
	return retorno;
}


int utn_obtenerTiempo(void){ //FUNCION PARA OBTENER EL TIEMPO
	return time(NULL);
}


int utn_tiempoFuturo(double secondsAdd){// FUNCION PARA CALCULAR UN TIEMPO FUTURO
	return secondsAdd + utn_obtenerTiempo();
}

