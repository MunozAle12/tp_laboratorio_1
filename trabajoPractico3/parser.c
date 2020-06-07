#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "Controller.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile,LinkedList* pArrayListEmployee)
{
	int respuesta = -3; //valor de retorno si no se pudo crear un empleado en memoria
	char auxiliarId[4096];
	char auxiliarNombre[4096];
	char auxiliarHorasTrabajadas[4096];
	char auxiliarSueldo[4096];
	int proximoId = 0;
	Employee* pAuxiliarEmpleado;
	do
	{
		if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",auxiliarId,auxiliarNombre,auxiliarHorasTrabajadas,auxiliarSueldo) == 4)
		{
			pAuxiliarEmpleado = employee_newParametrosTxt(auxiliarId,auxiliarNombre,auxiliarHorasTrabajadas,auxiliarSueldo);
			if(pAuxiliarEmpleado != NULL)
			{
				respuesta = -4; //valor de retorno si el puntero a la lista es null
				if(!ll_add(pArrayListEmployee,pAuxiliarEmpleado))
				{
					if(atoi(auxiliarId) >= proximoId)
					{
						proximoId = atoi(auxiliarId) + 1;
					}
				}
			}
		}
		else
		{
			break;
		}
	}while(!feof(pFile));
	fclose(pFile);
	respuesta = proximoId;
	return respuesta;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile,LinkedList* pArrayListEmployee)
{
	int respuesta = -3; //valor de retorno si no se pudo crear un empleado en memoria
	Employee auxiliarEmpleado;
	Employee* pAuxiliarEmpleado;
	int proximoId = 0;
	do
	{
		if(fread(&auxiliarEmpleado,sizeof(Employee),1,pFile) == 1)
		{
			pAuxiliarEmpleado = employee_newParametros(	auxiliarEmpleado.id,
														auxiliarEmpleado.nombre,
														auxiliarEmpleado.horasTrabajadas,
														auxiliarEmpleado.sueldo );
			if(pAuxiliarEmpleado != NULL)
			{
				respuesta = -4; //valor de retorno si el puntero a la lista es null
				if(!ll_add(pArrayListEmployee,pAuxiliarEmpleado))
				{
					if(auxiliarEmpleado.id >= proximoId)
					{
						proximoId = auxiliarEmpleado.id + 1;
					}
				}
			}
		}
	}while(!feof(pFile));
	fclose(pFile);
	respuesta = proximoId;
    return respuesta;
}
