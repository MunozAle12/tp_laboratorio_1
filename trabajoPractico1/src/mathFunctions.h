/*
 * mathFunctions.h
 *
 *  Created on: 13 abr. 2020
 *      Author: Usuario
 */

#ifndef MATHFUNCTIONS_H_
#define MATHFUNCTIONS_H_

int utn_Sumar(int* pResultado, int operador1,int operador2);	//Función que calcula la operación suma.
int utn_Restar(int* pResultado, int operador1,int operador2);	//Función que calcula la operación resta.
int utn_Multiply(int* pResultado, int operador1,int operador2);	//Función que calcula la operación multiplicación.
int utn_Dividir(float* pResultado, int operador1,int operador2);	//Función que calcula la operación división.
int utn_CalcularFactorial(int* pResultado, int operador);	//	Función que calcula el factorial de un número.

#endif /* MATHFUNCTIONS_H_ */
