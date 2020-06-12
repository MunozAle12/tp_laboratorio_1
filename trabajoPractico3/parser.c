#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "Controller.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param pFile Puntero al archivo que se desea leer.
 * \param pArrayListEmployee Puntero al espacio de memoria donde comienza la lista de empleados.
 * \return Retorna un valor tipo int mayor o igual a 0 que indica el proximo id disponible,
 * 		   -3 si no se pudo reservar espacio en memoria para un empleado.
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
				ll_add(pArrayListEmployee,pAuxiliarEmpleado);
				if(atoi(auxiliarId) >= proximoId)
				{
					proximoId = atoi(auxiliarId) + 1;
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
 * \param pFile Puntero al archivo que se desea leer.
 * \param pArrayListEmployee Puntero al espacio de memoria donde comienza la lista de empleados.
 * \return Retorna un valor tipo int mayor o igual a 0 que indica el proximo id disponible,
 * 		   -3 si no se pudo reservar espacio en memoria para un empleado.
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
				ll_add(pArrayListEmployee,pAuxiliarEmpleado);
				if(auxiliarEmpleado.id >= proximoId)
				{
					proximoId = auxiliarEmpleado.id + 1;
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
