/*
 * utn.c
 *
 *  Created on: 7 abr. 2020
 *      Author: Usuario
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int getInt(int* pResultado);	//Funci�n est�tica que busca y verifica si lo que se ingres� es un n�mero.
static int myGets(char* cadena, int longitud);	//Funci�n est�tica que guarda una lectura del archivo stdin de manera segura.
static int esNumericaInt(char* cadena);	//Funci�n est�tica que verifica una cadena num�rica.

/**
 * \brief utn_getNumeroInt Solicita el ingreso de un n�mero al usuario y luego de verificarlo devuelve un resultado.
 * \param pResultado Puntero al espacio de memoria donde se guardar� el n�mero verificado.
 * \param mensaje Es el mensaje a ser mostrado por pantalla.
 * \param mensajeError Es el mensaje de error a ser mostrado por pantalla.
 * \param minimo Es el n�mero maximo del rango de valores aceptados.
 * \param maximo Es el m�nimo del rango de valores a ser aceptados.
 * \return Retorna 0 si se obtuvo el numero y -1 si no.
 *
 */
int utn_getNumeroInt(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
	int bufferInt;
	int retorno = -1;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf("%s", mensaje);
			if(getInt(&bufferInt) == 0 && bufferInt >= minimo && bufferInt <= maximo)
			{
				*pResultado = bufferInt;
				retorno = 0;
				break;
			}
			reintentos--;
			printf("%s", mensajeError);
		}while(reintentos>=0);
	}
	return retorno;
}
/**
 * \brief getInt Busca y verifica si lo que se ingres� es un n�mero.
 * \param pResultado Puntero al espacio de memoria donde se dejar� el resultado de la funci�n.
 * \return Retorna 0 si se obtiene un numero entero y -1 si no.
 *
 */
static int getInt(int* pResultado)
{
    int retorno = -1;
    char bufferString[4096];

    if(myGets(bufferString, sizeof(bufferString)) == 0 && esNumericaInt(bufferString))
    {
    	retorno = 0;
    	*pResultado = atoi(bufferString);
    }
    return retorno;
}
/**
 * \brief myGets Guarda una lectura del archivo stdin hasta que encuentra un '\0'
 *                o hasta que haya copiado en cadena un m�ximo de 'longitud - 1' caracteres.
 * \param pCadena Puntero al espacio de memoria donde se copiara la cadena obtenida.
 * \param longitud Define el tama�o de pCadena.
 * \return Retorna 0 si se obtiene una cadena y -1 si no.
 *
 */
static int myGets(char* pCadena, int longitud)
{
	fflush(stdin);
	fgets(pCadena, longitud, stdin);
	pCadena[strlen(pCadena) - 1] = '\0';

	return 0;
}
/**
 * \brief esNumericaInt Verifica si la cadena ingresada es num�rica.
 * \param cadena Puntero a espacio de memoria donde guarda la cadena de caracteres a ser analizada.
 * \return Retorna 1 (vardadero) si la cadena es numerica y 0 (falso) si no lo es.
 *
 */
static int esNumericaInt(char* cadena)
{
	int retorno = 1;
	int i = 0;

	if(cadena[0] == '-' || cadena[0] == '+')
	{
		i = 1;
	}

	for( ; cadena[i] != '\0' ; i++)
	{
		if(cadena[i] > '9' || cadena[i] < '0')
		{
			retorno = 0;
			break;
		}
	}
	return retorno;
}
