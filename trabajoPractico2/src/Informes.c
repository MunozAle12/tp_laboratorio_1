/*
 * Informes.c
 *
 *  Created on: 15 may. 2020
 *      Author: Usuario
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "Empleado.h"

static int info_sortEmployees(Empleado* array,int limite);

/**
 * \brief Busca e informa lista de empleados en orden alfabético ascendente por apellido y sector
 * \param array Puntero al espacio de memoria donde comienza el array a analizar
 * \param limite Tamaño del array
 * \return Retorna 0 (EXITO), -1 (ERROR)
 */
int info_reportEmployeesList(Empleado* array, int limite)
{
	int respuesta = -1;

	if(info_sortEmployees(array,limite) != -1)
	{
		respuesta = 0;
		printf("Informe de empleados:\n");
		emp_printEmployees(array,limite);
	}
	return respuesta;
}
/**
 * \brief Ordena el array de empleados por doble criterio, por apellido y sector
 * \param array Puntero al espacio de memoria donde comienza el array de empleados
 * \param limite Tamaño del array de empleados
 * \return Retorna 0 si EXITO y -1 si ERROR
 *
 */
static int info_sortEmployees(Empleado* array,int limite)
{
	int respuesta = -1;
	int i;
	int flagSwap;
	Empleado auxiliar;
	int limiteComparacion;
	int auxComparacion;
	if(array != NULL && limite > 0)
	{
		limiteComparacion = limite-1;
		respuesta = 0;
		do
		{
			flagSwap = 0;
			for(i=0;i<limiteComparacion;i++)
			{
				auxComparacion = strncmp(array[i].apellido,array[i+1].apellido,APELLIDO_LEN);
				if( array[i].isEmpty == 0 &&
					array[i+1].isEmpty == 0 &&
					(auxComparacion > 0 || (auxComparacion == 0 && array[i].sector > array[i+1].sector)) )
				{
					auxiliar = array[i];
					array[i] = array[i+1];
					array[i+1] = auxiliar;
					flagSwap = 1;
				}
			}
			limiteComparacion--;
		}while(flagSwap);
	}
	return respuesta;
}
/**
 * \brief Busca e informa los salarios total y promedio de los empleados y la cantidad de los mismos que exceden el salario promedio
 * \param array Puntero al espacio de memoria donde comienza el array de empleados
 * \param limite Tamaño del array
 * \return Retorna 0 si EXITO, -1 si ERROR
 */
int info_reportEmployeesSalaries(Empleado* array,int limite)
{
	int respuesta = -1;
	float salarioTotal;
	float salarioPromedio;
	int cantidadEmpleados = 0;
	if(array != NULL && limite > 0)
	{
		if(emp_calculateSalary(array,limite,&salarioTotal,&salarioPromedio) != -1)
		{
			respuesta = 0;
			printf("El salario total de los empleados es: %.2f\n",salarioTotal);
			printf("El salario promedio de los empleados es: %.2f\n",salarioPromedio);
			if(emp_calculateEmployeesExceedAverageSalary(array,limite,salarioPromedio,&cantidadEmpleados) != -1)
			{
				printf("La cantidad de empleados que exeden el salario promedio es: %d\n",cantidadEmpleados);
			}
		}
	}
	return respuesta;
}
