/*
 ============================================================================
 Name        : trabajoPractico3.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 Menu:
 * 1. Cargar los datos de los empleados desde el archivo data.csv (modo texto)
 * 2. Cargar los datos de los empleados desde el archivo data.csv (modo binario)
 * 3. Alta de empleado
 * 4. Modificar datos de empleado
 * 5. Baja de empleado
 * 6. Listar empleados
 * 7. Ordenar empleados
 * 8. Guardar los datos de los empleados en el archivo data.csv (modo texto)
 * 9. Guardar los datos de los empleados en el archivo data.csv (modo binario)
 * 10. Salir
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "Empleado.h"
#define QTY_EMPLEADOS 2000
int main(void)
{
	setbuf(stdout,NULL);
	int opcion;
	Empleado* arrayPunterosEmpleados[QTY_EMPLEADOS];
	int proximoId = 0;
	int auxiliarId;
	char auxiliarNombre[NOMBRE_LEN];
	int auxiliarHorasTrabajadas;
	int auxiliarSueldo;
	int auxiliarIndice;
	int retorno;

	if(!empleado_initArray(arrayPunterosEmpleados,QTY_EMPLEADOS))
	{
		printf("ARRAY INICIALIZADO CON ÉXITO.\n");
		do
		{
			if(!utn_getNumero(&opcion,"\nElija una opción:\n"
									 "1) Cargar datos de los empleados desde archivo 'data.csv' (modo texto)\n"
									 "2) Cargar datos de los empleados desde archivo 'data.csv' (modo binario)\n"
									 "3) Alta de empleado\n"
									 "4) Modificar datos de empleado\n"
									 "5) Baja de empleado\n"
									 "6) Listar empleados\n"
									 "7) Ordenar empleados\n"
									 "8) Guardar datos de los empleados en archivo 'data.csv' (modo texto)\n"
									 "9) Guardar datos de los empleados en archivo 'data.csv' (modo binario)\n"
									 "10) Salir\n","\nOPCION INVALIDA.",1,10,2) )
			{
				switch(opcion)
				{
					case 1: //1) Cargar datos de los empleados desde archivo 'data.csv' (modo texto)
						retorno = empleado_parseEmpleado(arrayPunterosEmpleados,QTY_EMPLEADOS,"data.csv",&proximoId);
						switch(retorno)
						{
						case -1:
							printf("\nERROR. LOS PARAMETROS NO SON VALIDOS\n");
							break;
						case -2:
							printf("\nERROR AL ABRIR EL ARCHIVO.\n");
							break;
						default:
							printf("\n%d EMPLEADOS CARGADOS CON ÉXITO.\n",retorno);
						}
						break;
					case 2: //2) Cargar datos de los empleados desde archivo 'data.csv' (modo binario)
						retorno = empleado_parseEmpleadoBinario(arrayPunterosEmpleados,QTY_EMPLEADOS,"data.csv",&proximoId);
						switch(retorno)
						{
						case -1:
							printf("\nERROR. LOS PARAMETROS NO SON VALIDOS\n");
							break;
						case -2:
							printf("\nERROR AL ABRIR EL ARCHIVO.\n");
							break;
						default:
							printf("\n%d EMPLEADOS CARGADOS CON ÉXITO.\n",retorno);
						}
						break;
					case 3:	//3) Alta de empleado
						if( !utn_getNombre(auxiliarNombre,NOMBRE_LEN,"\nIngrese nombre: ","\n\nINGRESO INVALIDO.",2) &&
							!utn_getNumero(&auxiliarHorasTrabajadas,"\nIngrese horas trabajadas: ","\n\nINGRESO INVALIDO.",0,999,2) &&
							!utn_getNumero(&auxiliarSueldo,"\nIngrese sueldo: ","\n\nINGRESO INVALIDO.",0,999999,2) )
						{
							retorno = empleado_agregarEmpleadoArray(arrayPunterosEmpleados,QTY_EMPLEADOS,proximoId,auxiliarNombre,auxiliarHorasTrabajadas,auxiliarSueldo);
							switch(retorno)
							{
								case -1:
									printf("\nERROR. LOS PARAMETROS NO SON VÁLIDOS\n");
									break;
								case -2:
									printf("\nERROR. NO HAY ÍNDICE LIBRE\n");
									break;
								case -3:
									printf("\nERROR. NO SE PUDO AGREGAR EMPLEADO\n");
									break;
								default:
									printf("\nEMPLEADO AGREGADO CON ÉXITO.\n");
									proximoId++;
							}
						}
						break;
					case 4:	//4) Modificar datos de empleado
						if(!empleado_imprimirArray(arrayPunterosEmpleados,QTY_EMPLEADOS))
						{
							if(!utn_getNumero(&auxiliarId," \nIngresar ID de empleado a modificar: ","\n\nINGRESO INVALIDO.",0,proximoId,2))
							{
								auxiliarIndice = empleado_buscarPorIdArray(arrayPunterosEmpleados,QTY_EMPLEADOS,auxiliarId);
								if(auxiliarIndice >= 0)
								{
									if( !utn_getNombre(auxiliarNombre,NOMBRE_LEN,"\nModifique nombre: ","\n\nINGRESO INVALIDO.",2) &&
										!utn_getNumero(&auxiliarHorasTrabajadas,"\nModifique horas trabajadas: ","\n\nINGRESO INVALIDO.",0,999,2) &&
										!utn_getNumero(&auxiliarSueldo,"\nModifique sueldo: ","\n\nINGRESO INVALIDO.",0,999999,2) )
									{
										if( !empleado_setNombre(arrayPunterosEmpleados[auxiliarIndice],auxiliarNombre) &&
											!empleado_setHorasTrabajadas(arrayPunterosEmpleados[auxiliarIndice],auxiliarHorasTrabajadas) &&
											!empleado_setSueldo(arrayPunterosEmpleados[auxiliarIndice],auxiliarSueldo))
										{
											printf("\nEL ID: %d FUE MODIFICADO CON ÉXITO.\n",auxiliarId);
										}
										else
										{
											printf("\nERROR AL SETEAR DATOS.\n");
										}
									}
									else
									{
										printf("\nERROR AL MODIFICAR DE DATOS.\n");
									}
								}
								else
								{
									printf("\nNO EXISTE EL ID INGRESADO.\n");
								}
							}
							else
							{
								printf("\nSE ACABARON SUS REINTENTOS.\n");
							}
						}
						else
						{
							printf("\nERROR.\n");
						}
						break;
					case 5: //5) Baja de empleado
						if(!empleado_imprimirArray(arrayPunterosEmpleados,QTY_EMPLEADOS))
						{
							if(!utn_getNumero(&auxiliarId," \nIngresar ID de empleado a dar de baja: ","\n\nINGRESO INVALIDO.",0,proximoId,2))
							{
								auxiliarIndice = empleado_buscarPorIdArray(arrayPunterosEmpleados,QTY_EMPLEADOS,auxiliarId);
								if(auxiliarIndice >= 0)
								{
									if(!empleado_eliminarIndiceEnArray(arrayPunterosEmpleados,QTY_EMPLEADOS,auxiliarIndice))
									{
										printf("\nLA BAJA DEL EMPLEADO FUE UN ÉXITO.\n");
									}
									else
									{
										printf("\nERROR AL ELIMINAR EMPLEADO.\n");
									}
								}
								else
								{
									printf("\nNO EXISTE EL ID INGRESADO.\n");
								}
							}
							else
							{
								printf("\nSE ACABARON SUS REINTENTOS.\n");
							}
						}
						else
						{
							printf("\nERROR.\n");
						}
						break;
					case 6:	//6) Listar empleados
						if(empleado_imprimirArray(arrayPunterosEmpleados,QTY_EMPLEADOS) == -1)
						{
							printf("\nERROR.\n");
						}
						break;
					case 7:	//7) Ordenar empleados
						if(!empleado_ordenarArray(arrayPunterosEmpleados,QTY_EMPLEADOS))
						{
							if(empleado_imprimirArray(arrayPunterosEmpleados,QTY_EMPLEADOS) == -1)
							{
								printf("\nERROR.\n");
							}
						}
						else
						{
							printf("\nERROR AL ORDENAR EMPLEADOS.\n");
						}
						break;
					case 8:	//8) Guardar datos de los empleados en archivo 'data.csv' (modo texto)
						if(!empleado_guardarArrayEnArchivo(arrayPunterosEmpleados,QTY_EMPLEADOS,"data.csv"))
						{
							printf("\nDATOS GUARDADOS CON ÉXITO.\n");
						}
						break;
					case 9:	//9) Guardar datos de los empleados en archivo 'data.csv' (modo binario)
						if(!empleado_guardarArrayEnArchivoBinario(arrayPunterosEmpleados,QTY_EMPLEADOS,"data.csv"))
						{
							printf("\nDATOS GUARDADOS CON ÉXITO.\n");
						}
						break;
				}
			}
			else
			{
				printf("\nSE ACABARON SUS REINTENTOS.\n");
			}
		}while(opcion!=10);
	}
	return EXIT_SUCCESS;
}
