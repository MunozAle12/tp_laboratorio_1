/*
 * mathFunctions.c
 *
 *  Created on: 13 abr. 2020
 *      Author: Usuario
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * \brief utn_Sumar Función que suma dos números enteros y retorna el resultado por referencia.
 * \param pResultado Puntero al espacio de memoria donde se guardará el resultado de la operación.
 * \param operador1 Primer operando a calcular.
 * \param operador2 Segundo operando a calcular.
 * \return Retorna un 0 si se pudo calcular la suma, -1 si no.
 *
 */
int utn_Sumar(int* pResultado, int operador1,int operador2)
{
	int retorno = -1;

	if(pResultado != NULL && (operador1>=operador2 || operador1<=operador2))
	{
		*pResultado = operador1 + operador2;
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief utn_Restar Función que calcula la sustracción entre dos números enteros y retorna el resultado por referencia.
 * \param pResultado Puntero al espacio de memoria donde se guardará el resultado de la operación.
 * \param operador1 Primer operando a calcular.
 * \param operador2 Segundo operando a calcular.
 * \return Retorna un 0 si se pudo calcular la suma, -1 si no.
 *
 */
int utn_Restar(int* pResultado, int operador1,int operador2)
{
	int retorno = -1;

	if(pResultado != NULL && (operador1>=operador2 || operador1<=operador2))
	{
		*pResultado = operador1 - operador2;
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief utn_Multiply Función que calcula el producto entre dos números enteros y retorna el resultado por referencia.
 * \param pResultado Puntero al espacio de memoria donde se guardará el resultado de la operación.
 * \param operador1 Primer operando a calcular.
 * \param operador2 Segundo operando a calcular.
 * \return Retorna un 0 si se pudo calcular la suma, -1 si no.
 *
 */
int utn_Multiply(int* pResultado, int operador1,int operador2)
{
	int retorno = -1;

	if(pResultado != NULL && (operador1>=operador2 || operador1<=operador2))
	{
		*pResultado = operador1 * operador2;
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief utn_Dividir Función que calcula la división entre dos números enteros y retorna el cociente por referencia.
 * \param pResultado Puntero al espacio de memoria donde se guardará el resultado de la operación.
 * \param operador1 Dividendo.
 * \param operador2 Divisor.
 * \return Retorna un 0 si se pudo calcular la suma, -1 si no.
 *
 */
int utn_Dividir(float* pResultado, int operador1,int operador2)
{
	int retorno = -1;

	if(pResultado != NULL && operador2 != 0)
	{
		*pResultado = (float)operador1 / operador2;
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Función que calcula el factorial de un número y retorna el resultado por referencia.
 * \param pResultado Puntero al espacio de memoria donde se guardará el resultado de la operación.
 * \param operador Numero a ser calculado.
 * \return Retorna un 0 si se pudo calcular la suma, -1 si no.
 *
 */
int utn_CalcularFactorial(int* pResultado, int operador)
{
	int i;
	int retorno = -1;
	int resultado = 1;

	if(pResultado!=NULL && operador>=0)
	{
		for(i=operador; i>1; i--)
		{
			resultado = resultado * i;
		}
		*pResultado = resultado;
		retorno = 0;
	}
	return retorno;
}
