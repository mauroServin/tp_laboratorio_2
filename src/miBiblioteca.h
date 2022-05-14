/*
 * miBiblioteca.h
 *
 *  Created on: 14 may. 2022
 *      Author: 54116
 */

#ifndef MIBIBLIOTECA_H_
#define MIBIBLIOTECA_H_

int utn_getCaracter(char* pResultado, char* mensaje, char* mensajeError, char minimo, char maximo, int reintentos);
int utn_getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);
int utn_getNumeroFlotante(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos);
int utn_myGets(char* cadena, int longitud);
int utn_getNombre(char* pResultado, int longitud, char* mensaje, char* mensajeError, int reintentos);
int utn_getDescripcion(char* pResultado, int longitud, char* mensaje, char* mensajeError, int reintentos);

//FUNCIONES ARRAY
int utn_printArrayInt(int* pArray, int limite);
int utn_ordenarArrayInt(int* pArray, int limite);
int utn_initArrayFlotante(float* pArray, int longitud, float valorInicial);
int utn_printArrayFlotante(float* pArray, int longitud);

//FUNCIONES PARA APLIACIONES
void utn_menu();
int utn_cargarTemperaturas(float* pArray, int longitud);
int utn_imprimirNumeros(int* pArray, int limite);
int utn_solicitarNumeros(int* pArray, int limite);
int utn_borrarImpares(int* pArray, int limite);
int utn_ordenarNumeros(int* pArray, int limite);
int utn_contarPalabras(char cadena[], int len, int* pPalabras);

//FUNCIONES TIME
int utn_timeCurrent(void);
int utn_tiempoFuturo(double secondsAdd);

#endif /* MIBIBLIOTECA_H_ */
