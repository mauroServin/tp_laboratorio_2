/*
 * passenger.c
 *
 *  Created on: 14 may. 2022
 *      Author: 54116
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ArrayPassenger.h"
#include "miBiblioteca.h"


int eGen_ObtenerID(void) {
	//ID AUTOINCREMENTAL - PRIVADO / GLOBAL
	//INICIALIZADO UNA UNICA VEZ AL COMIENZO DEL PROGRAMA CON ALCANCE UNICAMENTE EN FUNCION eGen_ObtenerID();
	static int Gen_idIncremental = 0;
	return Gen_idIncremental++;
}

int initPassengers(ePassenger* array, int limite){
	int retorno = -1;

	if(array != NULL && limite > 0){
		retorno = 0;

		for(int i = 0; i < limite; i++){
			array[i].isEmpty = LIBRE;
		}
	}
	return retorno;
}


int addPassengers(ePassenger array[], int TAM) {
	int rtn = 0;
	ePassenger auxGen;

	//BUSCO ESPACIO EN ARRAY
	int index = eGen_ObtenerIndexLibre(array, TAM);

	//SI INDEX == -1 ARRAY LLENO
	//SI INDEX != -1 TENGO EN INDEX POSICION DE ARRAY LIBRE
	if (index != -1) {
		//PIDO DATOS - CARGO Gen AUXILIAR
		auxGen = eGen_CargarDatos();
		//SETEO ID UNICO - VARIABLE ESTATICA AUTOINCREMENTAL
		auxGen.id = eGen_ObtenerID();
		//CAMBIO SU ESTADO A "OCUPADO"
		auxGen.isEmpty = OCUPADO;
		//SETEO EL ARRAY CON AUXILIAR EN INDEX LIBRE OBTENIDO PREVIAMENTE
		array[index] = auxGen;

		//RETORNO 1 PARA SABER QUE FUE DADO DE ALTA SATISFACTORIAMENTE
		rtn = 1;
	}

	return rtn;
}

ePassenger eGen_CargarDatos(void) {
	ePassenger auxiliar;
	/** CARGAR DATOS NECESARIOS PARA EL ALTA*/
	/** IMPORTANTE - NO CARGAR ID NI ESTADO - SE HACE EN EL ALTA */

	utn_getNombre(auxiliar.name, TAM_NAME, "\nIngrese un nombre:", "\nError. Reintente.", 2);
	utn_getNombre(auxiliar.lastname, TAM_NAME, "\nIngrese un apellido:", "\nError.Reitente.", 2);
	utn_getNumeroFlotante(&auxiliar.price, "\nIngrese el precio de su viaje:", "\nError, precio inválido.", 0, 100000, 2);
	utn_getNombre(auxiliar.flycode, TAM_CODE, "\nIngrese un codigo de vuelo:", "\nError, codigo incorrecto", 2);
	utn_getNumero(&auxiliar.typePassenger, "\nIngrese un tipo de vuelo:\n\t1) TURISTA. \n\t2) PREMIUM. \n\t3) EJECUTIVO", "Error. tipo de vuelo invalido.", 1, 3, 2);
	utn_getNumero(&auxiliar.statusflight, "\nIngrese el estado de su vuelo:\n\t1) EMBARCANDO. \n\t2) VOLANDO. \n\t3) ATERRIZANDO", "Error, estado de vuelo invalido.", 1, 3, 2);

	return auxiliar;
}

int findPassengerById(ePassenger array[], int TAM, int ID) {
	int rtn = -1;
	int i;

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (array != NULL && TAM > 0) {
		//RECORRO TODO EL ARRAY
		for (i = 0; i < TAM; i++) {
			//BUSCO QUE ESTE "OCUPADO" Y QUE CONCIDA EL ID QUE ESTOY BUSCANDO
			if (array[i].id == ID && array[i].isEmpty == OCUPADO) {
				//SI ENCONTRE EL ID
				//DEVUELVO EL INDEX DE DONDE ESTA EL ID BUSCADO Y SALGO
				rtn = i;
				break;
			}
		}
	}

	return rtn;
}

int removePassenger(ePassenger array[], int TAM) {
	int rtn = 0;
	int idGen;
	int index;
	int flag = 0;

	//LISTO TODOS LOS Gen
	if (printPassengers(array, TAM)) {
		//BANDERA EN 1 SI HAY Gen DADOS DE ALTA PARA LISTAR
		flag = 1;
	}

	//SI HAY Gen PARA DAR DE BAJA
	if (flag) {
		//PIDO ID A DAR DE BAJA
		/**USAR FUNCION GET_INT DE LIBRERIA DE INPUTS*/
		printf("INGRESE ID A DAR DE BAJA: ");
		scanf("%d", &idGen);

		//BUSCO INDEX POR ID EN ARRAY
		while (findPassengerById(array, TAM, idGen) == -1) {
			puts("NO EXISTE ID.");

			/**USAR FUNCION GET_INT DE LIBRERIA DE INPUTS*/
			printf("INGRESE ID A DAR DE BAJA: ");
			scanf("%d", &idGen);
		}

		//OBTENGO INDEX DEL ARRAY DE Gen A DAR DE BAJA
		index = findPassengerById(array, TAM, idGen);

		/**PREGUNTAR SI DESEA CONTINUAR*/
		//BAJA ACEPTADA - CAMBIO ESTADO A "BAJA"
		array[index].isEmpty = BAJA;

		//RETORNO 1 SI SE DIO DE BAJA CORRECTAMENTE
		rtn = 1;
	}

	return rtn;
}


int sortPassengers(ePassenger array[], int TAM, int criterio) {
	int retorno = 0;
	int i;
	int flagSwap;
	ePassenger aux;

	/** EJEMPLO DE SORT CON ID DE Gen
	 MODIFICAR "CRITERIO DE ORDENAMIENTO" PARA OTROS CASOS DE ORDENAMIENTO
	 CASE -1 -> MENOR A MAYOR (ASCENDENTE)
	 CASE  1 -> MAYOR A MENOR (DESCENDENTE)
	 UTILIZAR strcmp(...) PARA COMPARAR CADENAS
	 */

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (array != NULL && TAM > 0) {
		switch (criterio) {
		case -1:
			do {
				flagSwap = 0;
				for (i = 0; i < TAM - 1; i++) {
					if (strncmp(array[i].lastname, array[i + 1].lastname,TAM_NAME) > 0||
						(strncmp(array[i].lastname, array[i + 1].lastname, TAM_NAME) == 0 && array[i].typePassenger < array[i + 1].typePassenger)) {

						flagSwap = 1;
						aux = array[i];
						array[i] = array[i + 1];
						array[i + 1] = aux;
					}
				}
				TAM--;
			} while (flagSwap);

			break;
		case 1:
			do {
				flagSwap = 0;
				for (i = 0; i < TAM - 1; i++) {
					if (strncmp(array[i].lastname, array[i + 1].lastname,TAM_NAME) > 0 ||
						(strncmp(array[i].lastname, array[i + 1].lastname, TAM_NAME) == 0 && array[i].typePassenger < array[i + 1].typePassenger)) {
						flagSwap = 1;
						aux = array[i];
						array[i] = array[i + 1];
						array[i + 1] = aux;
					}
				}
				TAM--;
			} while (flagSwap);
			break;
		default:
			//CRITERIO DE ORDENAMIENTO MAL INGRESADO
			retorno = 0;
			break;
		}
	}
	return retorno;
}


void eGen_MostrarUno(ePassenger Gen) {
	//PRINTF DE UN SOLO Gen
	printf("|%-3d|\t", Gen.id);
	printf("|%-10s|\t ", Gen.name);
	printf("|%-10s|\t ", Gen.lastname);
	printf("|%-10.2f|\t ", Gen.price);
	printf("|%-10s|\t ", Gen.flycode);
	switch(Gen.typePassenger){
	case 1:
		printf("|%-10s|\t ", "TURISTA");
	break;

	case 2:
		printf("|%-10s|\t ","PREMIUM");
	break;

	case 3:
		printf("|%-10s|\t ", "EJECUTIVO");
	break;
	}
	switch(Gen.statusflight){
	case -1:
		printf("|%-10s|\t ", "INACTIVO");
	break;

	case 0:
		printf("|%-10s|\t ", "DEMORADO");
	break;

	case 1:
		printf("|%-10s|\n ","ACTIVO");
	break;
	}
}


int printPassengers(ePassenger array[], int TAM) {
	int i;
	int rtn = 0;
	int cantidad = 0;

	//CABECERA
	puts("\n> LISTADO\n\n\t");
	printf("|%-3s|\t|%-10s|\t |%-10s|\t |%-10s|\t |%-10s|\t |%-10s|\t |%-10s|\t\n", "ID", "NOMBRE", "APELLIDO", "PRECIO", "CODIGO", "TIPO", "STATUS"); //AGREGAR TITULOS DE COLUMNA (QUITAR DE VER QUE NO ES NECESARIO)

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (array != NULL && TAM > 0) {
		//RECORRO TODO EL ARRAY
		for (i = 0; i < TAM; i++) {
			//PREGUNTO POR SU ESTADO "OCUPADO"
			if (array[i].isEmpty == OCUPADO) {
				//MUESTRO UN SOLO Gen
				eGen_MostrarUno(array[i]);
				//CONTADOR DE Gen
				cantidad++;
			}
		}
	}

	//SI CANTIDAD == 0 - NO HUBO Gen PARA MOSTRAR (ARRAY SIN ALTAS)
	if (cantidad > 0) {
		rtn = 1;
	}

	return rtn;
}


int sortPassengersByCode(ePassenger array[], int TAM, int criterio) {//REVISAR
	int retorno = 0;
	int i;
	int flagSwap;
	ePassenger aux;

	/** EJEMPLO DE SORT CON ID DE Gen
	 MODIFICAR "CRITERIO DE ORDENAMIENTO" PARA OTROS CASOS DE ORDENAMIENTO
	 CASE -1 -> MENOR A MAYOR (ASCENDENTE)
	 CASE  1 -> MAYOR A MENOR (DESCENDENTE)
	 UTILIZAR strcmp(...) PARA COMPARAR CADENAS
	 */

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (array != NULL && TAM > 0) {
		switch (criterio) {
		case -1:
			do {
				flagSwap = 0;
				for (i = 0; i < TAM - 1; i++) {
					if (strncmp(array[i].flycode, array[i + 1].flycode,TAM_NAME) > 0||
						(strncmp(array[i].flycode, array[i + 1].flycode, TAM_NAME) == 0 && array[i].statusflight < array[i + 1].statusflight)) {

						flagSwap = 1;
						aux = array[i];
						array[i] = array[i + 1];
						array[i + 1] = aux;
					}
				}
				TAM--;
			} while (flagSwap);

			break;
		case 1:
			do {
				flagSwap = 0;
				for (i = 0; i < TAM - 1; i++) {
					if (strncmp(array[i].lastname, array[i + 1].lastname,TAM_NAME) > 0 ||
						(strncmp(array[i].lastname, array[i + 1].lastname, TAM_NAME) == 0 && array[i].typePassenger < array[i + 1].typePassenger)) {
						flagSwap = 1;
						aux = array[i];
						array[i] = array[i + 1];
						array[i + 1] = aux;
					}
				}
				TAM--;
			} while (flagSwap);
			break;
		default:
			//CRITERIO DE ORDENAMIENTO MAL INGRESADO
			retorno = 0;
			break;
		}
	}
	return retorno;
}


int eGen_ObtenerIndexLibre(ePassenger array[], int TAM) {
	int rtn = -1;
	int i;

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (array != NULL && TAM > 0) {
		//RECORRO TODO EL ARRAY
		for (i = 0; i < TAM; i++) {
			//PREGUNTO POR EL ESTADO "LIBRE"
			if (array[i].isEmpty == LIBRE) {
				//OBTENGO EL PRIMER INDEX DEL VECTOR "LIBRE" Y SALGO
				rtn = i;
				break;
			}
		}
	}

	return rtn;
}

int eGen_hardcode(ePassenger* array, int limite, int indice, int id, char* nombre, char* apellido, float precio, char* codigo, int tipoPasajero,  int estado){
	int retorno = 0;
	ePassenger buffer;

	if(array != NULL && limite > 0 && indice < limite && indice >= 0){
		strncpy(buffer.name, nombre, TAM_NAME);
		strncpy(buffer.lastname, apellido, TAM_NAME);
		buffer.price = precio;
		buffer.typePassenger = tipoPasajero;
		buffer.isEmpty = OCUPADO;
		buffer.statusflight = estado;
		buffer.id = id;
		strncpy(buffer.flycode, codigo, TAM_CODE);
		array[indice] = buffer;
	}

	return retorno;
}

ePassenger eGen_ModificarUno(ePassenger Gen) {
	ePassenger auxiliar = Gen;
	int opcion;

	puts("\nINGRESE UN CAMPO A MODIFICAR.");
	utn_getNumero(&opcion, "\n\t1) NOMBRE.  \n\t2) APELLIDO. \n\t3) PRECIO. \n\t4) CODIGO DE VUELO. \n\t5) TIPO DE PASAJERO. \n\t6) ESTADO DE VUELO.", "ERROR, OPCION INVALIDA", 1, 6, 2);

	switch(opcion){
	case 1:
		utn_getNombre(Gen.name, TAM_NAME, "\nIngrese un nombre:", "\nError. Reintente.", 2);
		strncpy(auxiliar.name, Gen.name, TAM_NAME);
	break;

	case 2:
		utn_getNombre(Gen.lastname, TAM_NAME, "\nIngrese un apellido:", "\nError.Reitente.", 2);
		strncpy(auxiliar.lastname, Gen.lastname, TAM_NAME);
	break;

	case 3:
		utn_getNumeroFlotante(&Gen.price, "\nIngrese el precio de su viaje:", "\nError, precio inválido.", 0, 100000, 2);
		auxiliar.price = Gen.price;
	break;

	case 4:
		utn_getNombre(Gen.flycode, TAM_CODE, "\nIngrese un codigo de vuelo:", "\nError, codigo incorrecto", 2);
		strncpy(auxiliar.flycode,Gen.flycode, TAM_CODE);
	break;

	case 5:
		utn_getNumero(&Gen.typePassenger, "\nIngrese un tipo de vuelo:\n\t1) TURISTA. \n\t2) PREMIUM. \n\t3) EJECUTIVO", "Error. tipo de vuelo invalido.", 1, 3, 2);
		auxiliar.typePassenger = Gen.typePassenger;
	break;

	case 6:
		utn_getNumero(&Gen.statusflight, "\nIngrese el estado de su vuelo:\n\t 1) EMBARCANDO. \n\t2)VOLANDO. \n\t3)ATERRIZANDO", "Error, estado de vuelo invalido.", 1, 3, 2);
		auxiliar.statusflight = Gen.statusflight;
	break;
	}

	return auxiliar;
}

int eGen_Modificacion(ePassenger array[], int TAM) {
	int rtn = 0;
	int idGen;
	int index;
	int flag = 0;
	ePassenger auxiliar;

	//LISTO TODOS LOS Gen
	if (printPassengers(array, TAM)) {
		//BANDERA EN 1 SI HAY Gen DADOS DE ALTA PARA LISTAR
		flag = 1;
	}

	//SI HAY Gen PARA MODIFICAR
	if (flag) {
		//PIDO ID A MODIFICAR
		/**USAR FUNCION GET_INT DE LIBRERIA DE INPUTS*/
		utn_getNumero(&idGen, "INGRESE ID A MODIFICAR:", "ERROR, ID INVALIDO", 0, 2000, 2);

		//BUSCO INDEX POR ID EN ARRAY
		while (findPassengerById(array, TAM, idGen) == -1) {
			puts("NO EXISTE ID.");

			/**USAR FUNCION GET_INT DE LIBRERIA DE INPUTS*/
			utn_getNumero(&idGen, "INGRESE ID A MODIFICAR:", "ERROR, ID INVALIDO", 0, 2000, 2);
		}

		//OBTENGO INDEX DEL ARRAY DE Gen A MODIFICAR
		index = findPassengerById(array, TAM, idGen);

		//LLAMO A FUNCION QUE MODIFICA Gen
		auxiliar = eGen_ModificarUno(array[index]);

		/**PREGUNTAR SI DESEA CONTINUAR*/
		//MODIFICACION ACEPTADA
		array[index] = auxiliar;

		//RETORNO 1 SI SE MODIFICO CORRECTAMENTE
		rtn = 1;
	}

	return rtn;
}

int printPassengersActivos(ePassenger array[], int TAM) {
	int i;
	int rtn = 0;
	int cantidad = 0;

	//CABECERA
	puts("\n\t> LISTADO Gen");
	printf("%s\n\n", "ID"); //AGREGAR TITULOS DE COLUMNA (QUITAR DE VER QUE NO ES NECESARIO)

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (array != NULL && TAM > 0) {
		//RECORRO TODO EL ARRAY
		for (i = 0; i < TAM; i++) {
			//PREGUNTO POR SU ESTADO "OCUPADO"
			if (array[i].statusflight == ACTIVO) {
				//MUESTRO UN SOLO Gen
				eGen_MostrarUno(array[i]);
				//CONTADOR DE Gen
				cantidad++;
			}
		}
	}

	//SI CANTIDAD == 0 - NO HUBO Gen PARA MOSTRAR (ARRAY SIN ALTAS)
	if (cantidad > 0) {
		rtn = 1;
	}

	return rtn;
}

int calculoPrecio(ePassenger array[], int TAM){
	int retorno = -1;
	float precioPromedio = 0;
	float precioTotal= 0;
	int cantidad = 0;
	int masPromedio = 0;

	if(array != NULL && TAM > 0){
		for(int i = 0; i< TAM; i++){
			cantidad++;
			precioTotal = precioTotal + array[i].price;
			precioPromedio = precioTotal / cantidad;

			if(array[i].price > precioPromedio){
				masPromedio++;
			}
		}
	}
	printf("\nPRECIO TOTAL: %.2f --- PRECIO PROMEDIO: %.2f", precioTotal, precioPromedio);
	printf("\nPASAJEROS QUE SUPERAN EL PRECIO PROMEDIO: %d", masPromedio);

	return retorno;
}
