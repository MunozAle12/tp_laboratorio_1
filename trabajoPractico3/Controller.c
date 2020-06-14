#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "utn.h"

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path Puntero al espacio de memoria donde comienza la cadena que hace referencia al nombre del archivo.
 * \param pArrayListEmployee Puntero al espacio de memoria donde comienza la lista de empleados.
 * \return Retorna el valor que indica el próximo ID, -1 si los parametros recibidos no son válidos,
 * 		   -2 si hubo error al abrir el archivo, -3 si se pudo crear empleado en memoria.
 *
 */
int controller_loadFromText(char* path,LinkedList* pArrayListEmployee)
{
	int respuesta = -1; //valor de retorno si los parametros recibidos no son válidos
	FILE* fpArchivo;
	if(path != NULL && pArrayListEmployee != NULL)
	{
		respuesta = -2;	//valor de retorno si hubo error al abrir el archivo
		fpArchivo = fopen(path,"r");
		if(fpArchivo != NULL)	//¿ES REDUNDANTE ESTA VERIFICACIÓN?
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
		if(fpArchivo != NULL)	//¿ES REDUNDANTE ESTA VERIFICACIÓN?
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
	int respuesta = -1;	//valor de error si los parametros no son validos
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
	int respuesta = -1; //valor de retorno si los parametros no son válidos
	Employee* pAuxiliarEmpleado;
	char auxiliarNombre[NOMBRE_LEN];
	int auxiliarHorasTrabajadas;
	int auxiliarSueldo;
	if(pArrayListEmployee != NULL && proximoId >= 0 && ll_len(pArrayListEmployee) > 0)
	{
		respuesta = -2; //valor de retorno si no se encontró empleado
		if(employee_findEmployeeById(pArrayListEmployee,&pAuxiliarEmpleado,proximoId) >= 0)
		{
			respuesta = -3; //valor de retorno si se ingresó al menos un dato invalido
			if(!employee_requestEmployeeData(auxiliarNombre,&auxiliarHorasTrabajadas,&auxiliarSueldo))
			{
				respuesta = -4; // valor de retorno si no se logró asignar al menos un dato a un campo en la entidad
				if( !employee_setNombre(pAuxiliarEmpleado,auxiliarNombre) &&
					!employee_setHorasTrabajadas(pAuxiliarEmpleado,auxiliarHorasTrabajadas) &&
					!employee_setSueldo(pAuxiliarEmpleado,auxiliarSueldo) )
				{
					respuesta = 0; //valor de retorno si se logró modificar el empleado deseado
				}
			}
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
			employee_delete(pAuxiliarEmpleado);
			ll_remove(pArrayListEmployee,indexDelete);
			respuesta = 0; //valor de retorno si se elimino el empleado
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
	int respuesta = -1;
	int auxiliarLenLista;
	Employee* pAuxiliarEmpleado;
	int i;
	if(pArrayListEmployee != NULL && ll_len(pArrayListEmployee) > 0)
	{
		respuesta = 0;
		auxiliarLenLista = ll_len(pArrayListEmployee);
		for(i=0; i<auxiliarLenLista; i++)
		{
			pAuxiliarEmpleado = (Employee*)ll_get(pArrayListEmployee,i);
			printf("ID: %d - NOMBRE: %s - HORAS DE TRABAJO: %d - SUELDO: %d\n",pAuxiliarEmpleado->id,
																			   pAuxiliarEmpleado->nombre,
																			   pAuxiliarEmpleado->horasTrabajadas,
																			   pAuxiliarEmpleado->sueldo);
		}
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
