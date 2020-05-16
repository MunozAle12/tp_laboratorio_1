/*
 * Empleado.c
 *
 *  Created on: 28 abr. 2020
 *      Author: Usuario
 */

#include "Empleado.h"
#include "utn.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * \brief Inicializa el array de empleados
 * \param array Puntero al espacio de memoria donde comienza el array a ser actualizado
 * \param limite Tamaño del array a ser actualizado
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int emp_initEmployees(Empleado* array,int limite)
{
	int respuesta = -1;
	int i;
	if(array != NULL && limite > 0)
	{
		respuesta = 0;
		for(i=0; i<limite; i++)
		{
			array[i].isEmpty = 1;
		}
	}
	return respuesta;
}
/**
 * \brief Busca la primer posicion disponible del array
 * \param array Puntero al espacio de memoria donde comienza el array a ser actualizado
 * \param limite Tamaño del array a ser actualizado
 * \return Retorna el indice de la posicion vacia, -1 (ERROR)
 *
 */
int emp_getEmptyIndex(Empleado* array,int limite)
{
	int respuesta = -1;
	int i;
	if(array != NULL && limite > 0)
	{
		for(i=0; i<limite; i++)
		{
			if(array[i].isEmpty == 1)
			{
				respuesta = i;
				break;
			}
		}
	}
	return respuesta;
}
/**
 * \brief Da de alta un emplado en una posicion del array
 * \param array Puntero al espacio de memoria donde comienza el array a ser actualizado
 * \param limite Tamaño del array a ser actualizado
 * \param indice Posicion a ser actualizada
 * \param id Identificador a ser asignado al empleado
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int emp_addEmployee(Empleado* array,int limite,int indice,int* idEmpleado)
{
	int respuesta = -1;
	if(array != NULL && limite > 0 && indice < limite && idEmpleado != NULL)
	{
		if(	!utn_getNombre(array[indice].nombre, NOMBRE_LEN, "Ingrese nombre: \n", "\nNOMBRE INVALIDO. ",2) &&
			!utn_getApellido(array[indice].apellido,APELLIDO_LEN,"Ingrese apellido: \n","\nAPELLIDO NO VALIDO. ",2) &&
			!utn_getNumeroFlotante(&array[indice].salario,"Ingrese salario: \n","\nSALARIO INVALIDO. ",15000.00,32767.00,2) &&
			!utn_getNumero(&array[indice].sector,"Ingrese sector: \n","\nSECTOR INVALIDO. ",1,20,2) )
		{
			respuesta = 0;
			array[indice].isEmpty = 0;
			array[indice].id = *idEmpleado;
			(*idEmpleado)++;
		}
	}
	return respuesta;
}
/**
 * \brief Actualiza dato de un empleado en una posicion del array
 * \param array Puntero al espacio de memoria donde comienza el array a ser actualizado
 * \param limite Tamaño del array de empleados
 * \param indice Posición a ser actualizada
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int emp_modifyEmployee(Empleado* array,int limite,int indice)
{
	int respuesta = -1;
	int opcion;
	if(array != NULL && limite > 0 && indice < limite)
	do
	{
		if(!utn_getNumero(&opcion,"Ingrese opción para modificar dato:\n"
								  "1.Nombre\n"
								  "2.Apellido\n"
								  "3.Salario\n"
								  "4.Sector\n","\nOPCION INVALIDA. ",1,4,2) )
		{
			switch(opcion)
			{
				case 1:
					if(!utn_getNombre(array[indice].nombre, NOMBRE_LEN, "Modifique nombre: \n", "\nNOMBRE INVALIDO. ",2))
					{
						respuesta = 0;
						printf("\nSe modificó el nombre con éxito.\n");
					}
					else
					{
						printf("\nSe agotaron sus reitentos. Ingreso incorrecto.\n");
					}
					break;
				case 2:
					if(!utn_getApellido(array[indice].apellido,APELLIDO_LEN,"Modifique apellido: \n","\nAPELLIDO INVALIDO. ",2))
					{
						respuesta = 0;
						printf("\nSe modificó el apellido con éxito.\n");
					}
					else
					{
						printf("\nSe agotaron sus reitentos. Ingreso incorrecto.\n");
					}
					break;
				case 3:
					if(!utn_getNumeroFlotante(&array[indice].salario,"Modifique salario: \n","\nSALARIO INVALIDO. ",15000.00,32767.00,2))
					{
						respuesta = 0;
						printf("\nSe modificó el salario con éxito.\n");
					}
					else
					{
						printf("\nSe agotaron sus reitentos. Ingreso incorrecto.\n");
					}
					break;
				case 4:
					if(!utn_getNumero(&array[indice].sector,"Ingrese sector: \n","\nSECTOR INVALIDO. ",1,20,2))
					{
						respuesta = 0;
						printf("\nSe modificó el sector con éxito.\n");
					}
					else
					{
						respuesta = 0;
						printf("\nSe agotaron sus reitentos. Ingreso incorrecto.\n");
					}
					break;
			}
		}
	}while(opcion < 1 || opcion > 4);
	return respuesta;
}
/**
 * \brief Busca y verifica que haya cargado al menos un empleado en el array
 * \param array Puntero a espacio de memoria donde comienza el array a analizar
 * \param limite Tamaño del array a analizar
 * \return Retorna 0 si logró encontra al menos un empleado cargado, -1 si no.
 *
 */
int emp_findLoadedEmployees(Empleado* array,int limite)
{
	int respuesta = -1;
	int i;
	if(array != NULL && limite > 0)
	{
		for(i=0; i<limite; i++)
		{
			if(array[i].isEmpty != 1)
			{
				respuesta = 0;
			}
		}
	}
	return respuesta;
}

/**
 * \brief Busca y verifica si existe o no un ID en un array
 * \param array Array de empleados a ser analizado
 * \param limite Tamaño del array de empleados
 * \param valorBuscado valor del ID a ser buscado
 * \return Return Retorna el indice donde se encuentra el valor buscado, (-1) si no encuentra el valor buscado
 *
 */
int emp_findEmployeeById(Empleado* array,int limite,int valorBuscado)
{
    int retorno = -1;
    int i;
    if(array!= NULL && limite >= 0)
    {
        for(i=0; i<limite; i++)
        {
            if( array[i].isEmpty == 0 &&
            	array[i].id == valorBuscado)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}
/**
 * \brief Da de baja a un empleado en una posicion del array
 * \param array Puntero a espacio de memoria donde comienza el array a ser actualizado
 * \param limite Tamaño del array de empleados
 * \param indice Posición a ser actualizada
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int emp_removeEmployee(Empleado* array,int limite,int indice)
{
	int respuesta = -1;
	if(array != NULL && limite > 0 && indice < limite)
	{
		respuesta = 0;
		array[indice].isEmpty = 1;
	}
	return respuesta;
}
/**
 * \brief Imprime los datos de un empleado
 * \param pElemento Puntero al elemento del array que se busca imprimir
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int emp_printEmployee(Empleado* pElemento)
{
	int retorno = -1;
	if(pElemento != NULL)
	{
		retorno = 0;
		printf("ID: %d - Sector: %d - Apellido: %s - Nombre: %s - Salario: %.2f\n",pElemento->id,pElemento->sector,pElemento->apellido,pElemento->nombre,pElemento->salario);
	}
	return retorno;
}
/**
 * \brief Imprime el array de empleados
 * \param array Puntero al espacio de memoria donde comienza el array a ser actualizado
 * \param limite Tamaño del array a ser actualizado
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int emp_printEmployees(Empleado* array,int limite)
{
	int respuesta = -1;
	int i;
	if(array != NULL && limite > 0)
	{
		for(i=0; i<limite; i++)
		{
			if(array[i].isEmpty != 1)
			{
				respuesta = 0;
				emp_printEmployee(&array[i]);
			}
		}
	}
	return respuesta;
}
/**
 * \brief Busca y calcula el salario total y promedio de los empleados y retorna sus resultados por referencia
 * \param array Puntero al espacio de memoria donde comienza el array a ser analizado
 * \param limite Tamaño del array
 * \param pSalarioTotal Puntero al espacio de memoria donde se guardará el resultado del salario total de empleados
 * \param pSalarioPromedio Puntero al espacio de memoria donde se guardará el resultado del salario promedio de empleados
 * \return Retorna 0 si se logró calcular los salarios total y promedio, -1 si no.
 */
int emp_calculateSalary(Empleado* array,int limite,float* pSalarioTotal,float* pSalarioPromedio)
{
	int respuesta = -1;
	int i;
	float acumuladorSalario = 0;
	int contadorEmpleados = 0;
	if(array != NULL && limite > 0)
	{
		for(i=0; i<limite; i++)
		{
			if(array[i].isEmpty != 1)
			{
				respuesta = 0;
				contadorEmpleados++;
				acumuladorSalario = acumuladorSalario + array[i].salario;
			}
		}
		*pSalarioTotal = acumuladorSalario;
		*pSalarioPromedio = acumuladorSalario / (float)contadorEmpleados;
	}
	return respuesta;
}
/**
 * \brief Busca y calcula la cantidad de empleados que exeden el salario promedio y retorna su resultado por referencia
 * \param array Puntero al espacio de memoria donde comienza el array a ser analizado
 * \param limite Tamaño del array
 * \param promedio Valor del salario promedio de empleados
 * \param pCantidadEmpleados Puntero al espacio de memoria donde se guardará el total de empleados que exeden el salario promedio
 * \return Retorna 0 si se logró encontrar al menos un empleado, -1 si no.
 */
int emp_calculateEmployeesExceedAverageSalary(Empleado* array,int limite,float promedio,int* pCantidadEmpleados)
{
	int respuesta = -1;
	int i;
	if(array != NULL && limite > 0 && promedio > 0 && pCantidadEmpleados != NULL)
	{
		for(i=0; i<limite; i++)
		{
			if(array[i].isEmpty != 1 && array[i].salario > promedio)
			{
				(*pCantidadEmpleados)++;
				respuesta = 0;
			}
		}
	}
	return respuesta;
}
/* FUNCION PARA FORZAR ALTA DE EMPLEADOS */
/**
 * \brief Da de alta un empleado en una posicion del array modo DEBUG
 * \param array Puntero a espacio de memoria donde comienza el array a ser actualizado
 * \param limite Tamaño del array de empleados
 * \param indice Posicion a ser actualizada
 * \param idEmpleado Puntero a espacio de memoria donde se encuentra el ID a ser asignado
 * \param nombre Puntero a espacio de memoria donde se encuentra el ID a ser asignado
 * \param apellido Puntero a espacio de memoria donde se encuentra el apellido a ser asignado
 * \param salarioEmpleado Puntero a espacio de memoria donde se encuentra el salario a ser asignado
 * \param sectorEmpleado Puntero a espacio de memoria donde se encuentra el sector a ser asignado
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int emp_altaArrayDebug(Empleado* array,int limite,int indice,int* idEmpleado,char* nombre,char* apellido,float salarioEmpleado,int sectorEmpleado)
{
	int respuesta = -1;
	if(array!=NULL && limite>0 && indice<limite && nombre!=NULL && apellido!=NULL && salarioEmpleado > 0 && sectorEmpleado > 0)
	{
		respuesta = 0;
		strncpy(array[indice].nombre,nombre,NOMBRE_LEN);
		strncpy(array[indice].apellido,apellido,APELLIDO_LEN);
		array[indice].salario = salarioEmpleado;
		array[indice].sector = sectorEmpleado;
		array[indice].id = *idEmpleado;
		array[indice].isEmpty = 0;
		(*idEmpleado)++;
	}
	return respuesta;
}
