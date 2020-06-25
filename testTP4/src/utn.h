/*
 * utn.h
 *
 *  Created on: 30 may. 2020
 *      Author: Usuario
 */

#ifndef UTN_H_
#define UTN_H_

int utn_getNumero(int* pResultado,char* mensaje,char* mensajeError,int minimo,int maximo,int reintentos);
int utn_getNombre(char* pResultado,int longitud,char* mensaje,char* mensajeError,int reintentos);

#endif /* UTN_H_ */
