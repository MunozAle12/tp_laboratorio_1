/*
 * Controller.c
 *
 *  Created on: 20 jun. 2020
 *      Author: Usuario
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "Parser.h"
#include "utn.h"

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path Puntero al espacio de memoria donde comienza la cadena que hace referencia al nombre del archivo.
 * \param pArrayListEmployee Puntero al espacio de memoria donde comienza la lista de empleados.
 * \return Retorna el valor que indica el próximo ID, -1 si los parametros recibidos no son válidos,
 * 		   -2 si hubo error al abrir el archivo, -3 si se pudo crear empleado en memoria.
 *
 */
int controller_loadFromText(char* path, LinkedList* pArrayListEmployee)
{
	int respuesta = -1; //valor de retorno si los parametros recibidos no son válidos
	FILE* fpArchivo;
	if(path != NULL && pArrayListEmployee != NULL)
	{
		respuesta = -2;	//valor de retorno si hubo error al abrir el archivo
		fpArchivo = fopen(path,"r"); //ABRO EL ARCHIVO EN MODO LECTURA
		if(fpArchivo != NULL)
		{
			respuesta = parser_EmployeeFromText(fpArchivo,pArrayListEmployee); //valor de retorno que indica el proximo ID
		}
		fclose(fpArchivo);
	}
    return respuesta;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path Puntero al espacio de memoria donde comienza la cadena que hace referencia al nombre del archivo.
 * \param pArrayListEmployee Puntero al espacio de memoria donde comienza la lista de empleados.
 * \return Retorna el valor que indica el próximo ID, -1 si los parametros recibidos no son válidos,
 * 		   -2 si hubo error al abrir el archivo, -3 si se pudo crear empleado en memoria.
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int respuesta = -1; //valor de retorno si los parametros recibidos no son válidos
	FILE* fpArchivo;
	if(path != NULL && pArrayListEmployee != NULL)
	{
		respuesta = -2; //valor de retorno si hubo error al abrir el archivo
		fpArchivo = fopen(path,"rb");
		if(fpArchivo != NULL)
		{
			respuesta = parser_EmployeeFromBinary(fpArchivo,pArrayListEmployee); //valor de retorno que indica el proximo ID
		}
		fclose(fpArchivo);
	}
    return respuesta;
}

/** \brief Alta de empleados
 *
 * \param pArrayListEmployee Puntero a la posición de memoria donde comienza la lista de empleados.
 * \param id Valor del identificador a asignar al empleado
 * \return Retorna 0 si se pudo dar de alta a empleado, -1 si los parametros no son válidos o la lista está vacía,´
 * 		   -2 si se ingresó al menos un dato inválido, -3 si no se pudo crear empleado en memoria.
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee,int id)
{
	int respuesta = -1;	//valor de error si los parametros no son validos o si la lista está vacía
	Employee* pAuxiliarEmpleado;
	char auxiliarNombre[NOMBRE_LEN];
	int auxiliarHorasTrabajadas;
	int auxiliarSueldo;
	if(pArrayListEmployee != NULL && id >= 0 && ll_len(pArrayListEmployee) > 0)
	{
		respuesta = -2; //valor de error si se ingresó al menos un ingreso de dato invalido
		if(!employee_requestEmployeeData(auxiliarNombre,&auxiliarHorasTrabajadas,&auxiliarSueldo))
		{
			respuesta = -3; //valor de error si no se pudo agregar empleado en memoria
			pAuxiliarEmpleado = employee_newParametros(id,auxiliarNombre,auxiliarHorasTrabajadas,auxiliarSueldo);
			if(pAuxiliarEmpleado != NULL)
			{
				ll_add(pArrayListEmployee,pAuxiliarEmpleado);
				respuesta = 0;
			}
		}
	}
    return respuesta;
}

/** \brief Modificar datos de empleado
 *
 * \param pArrayListEmployee Puntero al espacio de memoria donde comienza la lista de empleados.
 * \param proximoId Valor del próximo ID a corresponder a empleado.
 * \return Retorna 0 si se logró modificar el empleado deseado, -4 si no se logró asignar al menos un dato
 * 		   a un campo en la entidad, -3 si se ingresó al menos un dato invalido, 2 si no se encontró empleado,
 * 		   -1 si los parametros no son válidos o la lista está vacía.
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee,int proximoId)
{
	int respuesta = -1; //valor de retorno si los parametros no son válidos o la lista está vacía
	Employee* pAuxiliarEmpleado;
	if(pArrayListEmployee != NULL && proximoId >= 0 && ll_len(pArrayListEmployee) > 0)
	{
		respuesta = -2; //valor de retorno si no se encontró empleado
		if(employee_findEmployeeById(pArrayListEmployee,&pAuxiliarEmpleado,proximoId) >= 0)
		{
			respuesta = employee_editEmployeeData(pAuxiliarEmpleado,employee_requestEmployeeData);
		}
	}
    return respuesta;
}

/** \brief Baja de empleado
 *
 * \param pArrayListEmployee Puntero al espacio de memoria donde comienza la lista de empleados.
 * \param proximoId Valor del próximo ID a corresponder a empleado.
 * \return Retorna 0 si se elimino el empleado deseado, -2 si no se encontró empleado en la lista,
 * 		   -1 si los parametros no son válidos o la lista está vacía.
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee,int proximoId)
{
	int respuesta = -1; //valor de retorno si los parametros no son válidos
	int indexDelete;
	Employee* pAuxiliarEmpleado;
	if(pArrayListEmployee != NULL && proximoId >= 0 && ll_len(pArrayListEmployee) > 0)
	{
		respuesta = -2; //valor de retorno si no se encontró empleado en la lista
		indexDelete = employee_findEmployeeById(pArrayListEmployee,&pAuxiliarEmpleado,proximoId);
		if(indexDelete >= 0)
		{
			respuesta = 0; //valor de retorno si se elimino el empleado
			employee_delete(pAuxiliarEmpleado);
			ll_remove(pArrayListEmployee,indexDelete);
		}
	}
    return respuesta;
}

/** \brief Listar empleados
 *
 * \param pArrayListEmployee Puntero a espacio de memoria donde comienza la lista de empleados.
 * \return Retorna 0 si se logró imprimir lista de empleados, -1 si error.
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int respuesta = -2;
	if(pArrayListEmployee != NULL && ll_len(pArrayListEmployee) > 0)
	{
		respuesta = ll_map(pArrayListEmployee,employee_printEmployee);
	}
	return respuesta;
}

/** \brief Ordenar empleados
 *
 * \param pArrayListEmployee Puntero a espacio de memoria donde comienza la lista de empleados.
 * \return Retorna 0 si se logró ordenar empleados, -1 si los parametros no son válidos o la lista esta vacía.
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int respuesta = -2;
	int opcionOrden;
	int opcionCriterio;
    if(pArrayListEmployee != NULL && ll_len(pArrayListEmployee) > 0)
    {
    	if( !utn_getNumero(&opcionOrden,"Para establecer el orden, elija una opción:\n"
    									"1) Orden ascendente\n"
    									"0) Orden descendente\n","\nINGRESO INVÁLIDO. ",0,1,2) &&
    		!utn_getNumero(&opcionCriterio,"Para establecer un criterio, elija una opción:\n"
    									   "1) Ordenar por ID\n"
    									   "2) Ordenar por nombre\n"
    									   "3) Ordenar por horas trabajadas\n"
    									   "4) Ordenar por sueldo\n","\nINGRESO INVÁLIDO. ",1,4,2) )
    	{
    		switch(opcionCriterio)
    		{
				case 1:
					respuesta = ll_sort(pArrayListEmployee,employee_sortById,opcionOrden);
					break;
				case 2:
					respuesta = ll_sort(pArrayListEmployee,employee_sortByNombre,opcionOrden);
					break;
				case 3:
					respuesta = ll_sort(pArrayListEmployee,employee_sortByHorasTrabajadas,opcionOrden);
					break;
				case 4:
					respuesta = ll_sort(pArrayListEmployee,employee_sortBySueldo,opcionOrden);
					break;
    		}
    	}
    }
	return respuesta;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path Puntero al espacio de memoria donde comienza la cadena que hace referencia al archivo.
 * \param pArrayListEmployee Puntero al espacio de memoria donde comienza la lista de empleados.
 * \return Retorna 0 si se guardó datos de empleados en modo texto, -2 si hubo error al abrir el archivo,
 * 		   -1 si los parametros recibidos no son válidos o la lista está vacía.
 *
 */
int controller_saveAsText(char* path,LinkedList* pArrayListEmployee)
{
	int respuesta = -1; //valor de retorno si los parametros no son válidos
	FILE* fpArchivo;
	int i;
	int auxiliarLenLista;
	Employee* pAuxiliarEmpleado;
	int auxiliarId;
	char auxiliarNombre[NOMBRE_LEN];
	int auxiliarHorasTrabajadas;
	int auxiliarSueldo;
	if(path != NULL && pArrayListEmployee != NULL && ll_len(pArrayListEmployee) > 0)
	{
		respuesta = -2; //valor de retorno si hubo error al abrir el archivo
		fpArchivo = fopen(path,"w");
		if(fpArchivo != NULL)
		{
			respuesta = 0; //valor de retorno si se logró guardar datos de empleados en modo texto
			auxiliarLenLista = ll_len(pArrayListEmployee);
			for(i=0; i<auxiliarLenLista; i++)
			{
				pAuxiliarEmpleado = (Employee*)ll_get(pArrayListEmployee,i);
				if(	!employee_getId(pAuxiliarEmpleado,&auxiliarId) &&
					!employee_getNombre(pAuxiliarEmpleado,auxiliarNombre) &&
					!employee_getHorasTrabajadas(pAuxiliarEmpleado,&auxiliarHorasTrabajadas) &&
					!employee_getSueldo(pAuxiliarEmpleado,&auxiliarSueldo) )
				{
					fprintf(fpArchivo,"%d,%s,%d,%d\n",auxiliarId,auxiliarNombre,auxiliarHorasTrabajadas,auxiliarSueldo);
				}
			}
			fclose(fpArchivo);
		}
	}
    return respuesta;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path Puntero al espacio de memoria donde comienza la cadena que hace referencia al archivo.
 * \param pArrayListEmployee Puntero al espacio de memoria donde comienza la lista de empleados.
 * \return Retorna 0 si se guardó datos de empleados en modo texto, -2 si hubo error al abrir el archivo,
 * 		   -1 si los parametros recibidos no son válidos o la lista esta vacía.
 *
 */
int controller_saveAsBinary(char* path,LinkedList* pArrayListEmployee)
{
	int respuesta = -1;
	FILE* fpArchivo;
	int i;
	int auxiliarLenLista;
	Employee* pAuxiliarEmpleado;
	if(path != NULL && pArrayListEmployee != NULL && ll_len(pArrayListEmployee) > 0)
	{
		respuesta = -2;
		fpArchivo = fopen(path,"wb");
		if(fpArchivo != NULL)
		{
			respuesta = 0;
			auxiliarLenLista = ll_len(pArrayListEmployee);
			for(i=0; i<auxiliarLenLista; i++)
			{
				pAuxiliarEmpleado = ll_get(pArrayListEmployee,i);
				fwrite(pAuxiliarEmpleado,sizeof(Employee),1,fpArchivo);
			}
			fclose(fpArchivo);
		}
	}
    return respuesta;
}

/*
============================================================================
						NUEVAS FUNCIONES DE CONTROLLER
============================================================================
*/

/**
 * \brief Inicializa dato de los empleados de la lista.
 *
 * \param pArrayListEmployee Puntero al espacio de memoria donde comienza la lista de empleados.
 * \return Retorna -2 si los parametros recibidos son NULL, -1 si al menos un elemento no cumple con el criterio establecido,
 * 				   retorna 0 si se inicializó con éxito.
 *
 */
int controller_InitEmployeeDataOfList(LinkedList* pArrayListEmployee) //NUEVA
{
	int respuesta = -2;
	int option;
	if(pArrayListEmployee != NULL && ll_len(pArrayListEmployee) > 0)
	{
		if(!utn_getNumero(&option,"Ingrese dato de empleado a inicializar en la lista\n"
								  "1) Horas de trabajo\n"
								  "2) Sueldo\n","\nINGRESO INVALIDO. ",1,2,2))
		{
			switch(option)
			{
				case 1:
					respuesta = ll_map(pArrayListEmployee,employee_initMemberHorasTrabajadas);
					break;
				case 2:
					respuesta = ll_map(pArrayListEmployee,employee_initMemberSueldo);
					break;
			}
		}
	}
	return respuesta;
}

/**
 * \brief Calcula el salario de cada uno de los empleados de la lista.
 *
 * \param pArrayListEmployee Puntero al espacio de memoria donde comienza la lista de empleados.
 * \return -2 si los parametros recibidos son NULL, -1 si al menos un elemento no cumple con el criterio establecido,
 * 		   retirna 0 si se calculó los salarios con éxito.
 *
 */
int controller_calculateEmployeeSalary(LinkedList* pArrayListEmployee) //NUEVA
{
	int respuesta = -2;
	if(pArrayListEmployee != NULL && ll_len(pArrayListEmployee) > 0)
	{
		respuesta = ll_map(pArrayListEmployee,employee_calcularSueldo);
	}
	return respuesta;
}

/**
 * \brief Informa los empleados de la lista que trabajan más de 100 horas.
 *
 * \param pArrayListEmployee Puntero al espacio de memoria donde comienza la lista de empleados.
 * \return -1 si los parametros recibidos son NULL, -2 si no se logró crear una lista filtrada,
 *		   0 si se logró informar de manera exitosa.
 *
 */
int controller_reportingEmployeesWithMoreThan100WorkingHours(LinkedList* pArrayListEmployee) //NUEVA
{
	int respuesta = -1;
	LinkedList* employeeReportingList;
	int qtyEmployees;
	if(pArrayListEmployee != NULL && ll_len(pArrayListEmployee) > 0)
	{
		respuesta = -2;
		employeeReportingList = ll_filter(pArrayListEmployee,employee_trabajaMasDe100Horas);
		if( employeeReportingList != NULL &&
			!ll_map(employeeReportingList,employee_printEmployee) )
		{
			qtyEmployees = ll_count(employeeReportingList,employee_trabajaMasDe100Horas);
			ll_map(employeeReportingList,employee_printEmployee);
			respuesta = qtyEmployees;
		}
	}
	return respuesta;
}
 /**
  * \brief Informa el saldo total a pagar por todos sueldos.
  *
  * \param pArrayListEmployee Puntero al espacio de memoria donde comienza la lista de empleados.
  * \return -2 si los parametros recibidos son NULL, Retorna -1 si hubo error al calcular el saldo total,
  * 		un valor mayor o igual a 0 el cual representa el valor acumulado.
  *
  */
int controller_reportingTotalSalaryBalance(LinkedList* pArrayListEmployee) //NUEVA
{
	int respuesta = -2; //int respuesta = -2;
	if(pArrayListEmployee != NULL && ll_len(pArrayListEmployee) > 0)
	{
		respuesta = ll_accumulatorInt(pArrayListEmployee,employee_acumularSueldo);
	}
	return respuesta;
}

/**
 * \brief Informa el empleado de la lista con mayor sueldo.
 *
 * \param pArrayListEmployee Puntero al espacio de memoria donde comienza la lista de empleados.
 * \return -1 si los parametros recibidos son NULL, -2 si no se logró reducir la lista, 0 si se redujo la lista con éxito.
 *
 */
int controller_informarEmpleadoConMayorSueldo(LinkedList* pArrayListEmployee) //NUEVA
{
	int respuesta = -1;
	void* pElementReporting;
	if(pArrayListEmployee != NULL && ll_len(pArrayListEmployee) > 0)
	{
		respuesta = -2;
		pElementReporting = ll_reduceInt(pArrayListEmployee,employee_compararSueldoPorMayor);
		if(pElementReporting != NULL)
		{
			respuesta = 0;
			printf("EL EMPLEADO CON MAYOR SUELDO ES:\n");
			employee_printEmployee(pElementReporting);
		}
	}
	return respuesta;
}
