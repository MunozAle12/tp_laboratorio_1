/*
 * utn.h
 *
 *  Created on: 30 may. 2020
 *      Author: Usuario
 */

#ifndef UTN_H_
#define UTN_H_

int utn_getNumero(int* pResultado,char* mensaje,char* mensajeError,int minimo,int maximo,int reintentos);
int utn_getNumeroFlotante(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos);
int utn_getNombre(char* pResultado,int longitud,char* mensaje,char* mensajeError,int reintentos);
int utn_getApellido(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos);
int utn_getTexto(char* pResultado,int longitud,char* mensaje,char* mensajeError,int reintentos);
int utn_getCuit(char* pResultado,int longitud,char* mensaje,char* mensajeError,int reintentos);
int utn_getLetra(char* pResultado,char* mensaje,char* mensajeError,int reintentos);
int utn_initArrayInt(int* array,int len);

#endif /* UTN_H_ */
