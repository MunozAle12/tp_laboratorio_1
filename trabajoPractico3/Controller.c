#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "utn.h"


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path,LinkedList* pArrayListEmployee)
{
	int respuesta = -1; //valor de retorno si los parametros recibidos no son v�lidos
	FILE* fpArchivo;
	if(path != NULL && pArrayListEmployee != NULL)
	{
		respuesta = -2;	//valor de retorno si hubo error al abrir el archivo
		fpArchivo = fopen(path,"r");
		if(fpArchivo != NULL)
		{
			respuesta = parser_EmployeeFromText(fpArchivo,pArrayListEmployee); //valor de retorno que indica el proximo ID
		}
	}
    return respuesta;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int respuesta = -1;
	FILE* fpArchivo;
	if(path != NULL && pArrayListEmployee != NULL)
	{
		respuesta = -2;
		fpArchivo = fopen(path,"rb");
		if(fpArchivo != NULL)
		{
			respuesta = parser_EmployeeFromBinary(fpArchivo,pArrayListEmployee);
		}
	}
    return respuesta;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee,int id)
{
	int respuesta = -1;	//valor de error si los parametros no son validos
	Employee* pAuxiliarEmpleado;
	char auxiliarNombre[NOMBRE_LEN];
	int auxiliarHorasTrabajadas;
	int auxiliarSueldo;
	if(pArrayListEmployee != NULL && id > 0)
	{
		respuesta = -2; //valor de error si se ingres� al menos un ingreso de dato invalido
		if( !utn_getNombre(auxiliarNombre,NOMBRE_LEN,"\nIngrese nombre: ","\n\nINGRESO INVALIDO.",2) &&
			!utn_getNumero(&auxiliarHorasTrabajadas,"\nIngrese horas trabajadas: ","\n\nINGRESO INVALIDO.",0,999,2) &&
			!utn_getNumero(&auxiliarSueldo,"\nIngrese sueldo: ","\n\nINGRESO INVALIDO.",0,999999,2) )
		{
			respuesta = -3; //valor de error si no se pudo agregar empleado
			pAuxiliarEmpleado = employee_newParametros(id,auxiliarNombre,auxiliarHorasTrabajadas,auxiliarSueldo);
			if(pAuxiliarEmpleado != NULL)
			{
				respuesta = -4; //valor de error si el puntero a la lista es null
				if(!ll_add(pArrayListEmployee,pAuxiliarEmpleado))
				{
					respuesta = 0;
				}
			}
		}
	}
    return respuesta;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee,int proximoId)
{
	int respuesta = -1; //valor de retorno si los parametros no son v�lidos
	int idBuscado;
	int auxiliarId;
	int i;
	int auxiliarLenLista;
	Employee* pAuxiliarEmpleado;
	char auxiliarNombre[NOMBRE_LEN];
	int auxiliarHorasTrabajadas;
	int auxiliarSueldo;
	if(pArrayListEmployee != NULL && proximoId >= 0)
	{
		respuesta = -2; //valor de retorno si se ingres� ID invalido
		if(!utn_getNumero(&idBuscado," \nIngresar ID de empleado a modificar: ","\n\nINGRESO INVALIDO.",0,proximoId,2))
		{
			auxiliarLenLista = ll_len(pArrayListEmployee);
			for(i=0; i<auxiliarLenLista; i++)
			{
				respuesta = -3; //valor de retorno si el puntero a la lista es NULL o el indice es erroneo
				pAuxiliarEmpleado = (Employee*)ll_get(pArrayListEmployee,i);
				if(pAuxiliarEmpleado != NULL)
				{
					respuesta = -4; //valor de retorno si no se obtuvo ID
					if(!employee_getId(pAuxiliarEmpleado,&auxiliarId))
					{
						if(idBuscado == auxiliarId)
						{
							respuesta = -5; //valor de retorno si se ingres� al menos un dato invalido
							if( !utn_getNombre(auxiliarNombre,NOMBRE_LEN,"\nIngrese nombre: ","\n\nINGRESO INVALIDO.",2) &&
								!utn_getNumero(&auxiliarHorasTrabajadas,"\nIngrese horas trabajadas: ","\n\nINGRESO INVALIDO.",0,999,2) &&
								!utn_getNumero(&auxiliarSueldo,"\nIngrese sueldo: ","\n\nINGRESO INVALIDO.",0,999999,2) )
							{
								respuesta = -6; // valor de retorno si no se logr� asignar al menos un dato a un campo en la entidad
								if( !employee_setNombre(pAuxiliarEmpleado,auxiliarNombre) &&
									!employee_setHorasTrabajadas(pAuxiliarEmpleado,auxiliarHorasTrabajadas) &&
									!employee_setSueldo(pAuxiliarEmpleado,auxiliarSueldo))
								{
									respuesta = 0; //valor de retorno si se logr� modificar el empleado deseado
									break;
								}
							}

						}
					}
				}
			}
		}
	}
    return respuesta;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee,int proximoId)
{
	int respuesta = -1; //valor de retorno si los parametros no son v�lidos
	int idBuscado;
	int auxiliarLenLista;
	int i;
	Employee* pAuxiliarEmpleado;
	int auxiliarId;
	if(pArrayListEmployee != NULL && proximoId >= 0)
	{
		respuesta = -2; //valor de retorno si se ingres� ID invalido
		if(!utn_getNumero(&idBuscado,"\nIngresar ID de empleado a dar de baja: ","\n\nINGRESO INVALIDO.",0,proximoId,2))
		{
			auxiliarLenLista = ll_len(pArrayListEmployee);
			for(i=0; i<auxiliarLenLista; i++)
			{
				respuesta = -3; //valor de retorno si el puntero a la lista es NULL o el indice es erroneo
				pAuxiliarEmpleado = (Employee*)ll_get(pArrayListEmployee,i);
				if(pAuxiliarEmpleado != NULL)
				{
					respuesta = -4; //valor de retorno si no se obtuvo ID
					if(!employee_getId(pAuxiliarEmpleado,&auxiliarId))
					{
						if(idBuscado == auxiliarId)
						{
							respuesta = -5; //valor de retorno si el puntero a la lista es null o el indice es erroneo
							if(!ll_remove(pArrayListEmployee,i))
							{
								employee_delete(pAuxiliarEmpleado);
								respuesta = 0; //valor de retorno si se elimino el empleado
								break;
							}
						}
					}
				}
			}
		}
	}
    return respuesta;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int respuesta = -1;
	int auxiliarLenLista;
	Employee* pAuxiliarEmpleado;
	int i;
	if(pArrayListEmployee != NULL)
	{
		respuesta = 0;
		auxiliarLenLista = ll_len(pArrayListEmployee);
		for(i=0; i<auxiliarLenLista; i++)
		{
			pAuxiliarEmpleado = (Employee*)ll_get(pArrayListEmployee,i);
			printf("Index: %d - ID: %d - NOMBRE: %s - HORAS DE TRABAJO: %d - SUELDO: %d\n",i,
																						   pAuxiliarEmpleado->id,
																						   pAuxiliarEmpleado->nombre,
																						   pAuxiliarEmpleado->horasTrabajadas,
																						   pAuxiliarEmpleado->sueldo);
		}
	}
    return respuesta;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int respuesta = -1;
    if(pArrayListEmployee != NULL)
    {
		if(!ll_sort(pArrayListEmployee,employee_sortByNombre,1))
		{
			respuesta = 0;
		}
    }
	return respuesta;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path,LinkedList* pArrayListEmployee)
{
	int respuesta = -1; //valor de retorno si los parametros no son v�lidos
	FILE* fpArchivo;
	int i;
	int auxiliarLenLista;
	Employee* pAuxiliarEmpleado;
	int auxiliarId;
	char auxiliarNombre[NOMBRE_LEN];
	int auxiliarHorasTrabajadas;
	int auxiliarSueldo;
	if(path != NULL && pArrayListEmployee != NULL)
	{
		respuesta = -2; //valor de retorno si hubo error al abrir el archivo
		fpArchivo = fopen(path,"w");
		if(fpArchivo != NULL)
		{
			respuesta = 0;
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
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path,LinkedList* pArrayListEmployee)
{
	int respuesta = -1;
	FILE* fpArchivo;
	int i;
	int auxiliarLenLista;
	Employee* pAuxiliarEmpleado;
	if(path != NULL && pArrayListEmployee != NULL)
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

