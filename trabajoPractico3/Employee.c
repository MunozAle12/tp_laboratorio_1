#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"
#include "LinkedList.h"

static int isValidId(char* cadena, int limite);
static int isValidNombre(char* cadena,int longitud);
static int isValidHoras(char* cadena, int limite);
static int isValidSueldo(char* cadena, int limite);

/**
 * \brief Reserva de manera dinámica espacio de memoria para un empleado.
 *
 * \return Retorna un puntero a una longitud de bytes asignado para un empleado o
 * 		   NULL si no se pudo asiganar espacio en memoria.
 *
 */
Employee* employee_new(void)
{
	Employee* punteroAuxiliar = NULL;
	punteroAuxiliar = (Employee*) malloc(sizeof(Employee));
	return punteroAuxiliar;
	//return (Employee*)malloc(sizeof(Employee));
}

/**
 * \brief Crea un empleado en memoria. Convierte y asigna un valor válido a miembros de la entidad.
 *
 * \param idStr Puntero a cadena que refiere a un ID.
 * \param nombreStr Puntero a cadena que refiere a un nombre de un empleado.
 * \param horasTrabajadasStr Puntero a cadena que refiere a horas trabajadas de un empleado.
 * \param sueldoStr Puntero a cadena que refiere a sueldo de un empleado.
 * \return Retorna un puntero a una longitud de bytes asignado para un empleado o
 * 		   NULL si no se pudo asiganar espacio en memoria.
 *
 */
Employee* employee_newParametrosTxt(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* sueldoStr)
{
	Employee* this = NULL;
	this = employee_new();
	if(this != NULL && idStr != NULL && nombreStr != NULL && horasTrabajadasStr != NULL && sueldoStr != NULL)
	{
		if(	employee_setIdTxt(this,idStr) == -1 ||
			employee_setNombre(this,nombreStr) == -1 ||
			employee_setHorasTrabajadasTxt(this,horasTrabajadasStr) == -1 ||
			employee_setSueldoTxt(this,sueldoStr) == -1 )
		{
			employee_delete(this);
			this = NULL;
		}
	}
	return this;
}

/**
 * \brief Crea un empleado en memoria, convierte y asigna un valor válido a miembros de la entidad.
 *
 * \param id Valor que refiere a un ID de un empleado.
 * \param nombre Puntero a cadena que refiere a un nombre de un empleado.
 * \param horasTrabajadas Valor que refiere a horas trabajadas de un empleado.
 * \param sueldo Valor que refiere a sueldo de un empleado.
 * \return Retorna un puntero a una longitud de bytes asignado para un empleado o
 * 		   NULL si no se pudo asiganar espacio en memoria.
 *
 */
Employee* employee_newParametros(int id,char* nombre,int horasTrabajadas,int sueldo)
{
	Employee* this = NULL;
	this = employee_new();
	if(this != NULL && nombre != NULL)
	{
		if(	employee_setId(this,id) == -1 ||
			employee_setNombre(this,nombre) == -1 ||
			employee_setHorasTrabajadas(this,horasTrabajadas) == -1 ||
			employee_setSueldo(this,sueldo) == -1 )
		{
			employee_delete(this);
			this = NULL;
		}
	}
	return this;
}

/**
 * \brief Libera el bloque de memoria al que apunta this.
 *
 * \param this Puntero a espacio de memoria donde comienza el bloque de bytes asignado para un empleado
 * \return Retorna void
 *
 */
void employee_delete(Employee* this)
{
	if(this != NULL)
	{
		free(this);
	}
}

/**
 * \brief Valida y asigna un id a un empleado
 *
 * \param this Puntero al bloque de bytes asignado al empleado que se desea setear.
 * \param id Valor de ID a ser asignado.
 * \return Retorna 0 (ÉXITO) si se logró asignar, -1 (ERROR) si no.
 *
 */
int employee_setId(Employee* this,int id)
{
	int retorno = -1;
	if(this != NULL && id >= 0)
	{
		retorno = 0;
		this->id = id;
	}
	return retorno;
}

/**
 * \brief Obtiene el id de un empleado
 *
 * \param this Puntero al bloque de bytes asignado al empleado que se desea leer.
 * \param id Puntero a espacio de memoria donde se guardará el valor de ID leído.
 * \return Retorna 0 (ÉXITO) si se logró leer, -1 (ERROR) si no.
 *
 */
int employee_getId(Employee* this,int* id)
{
	int retorno = -1;
	if(this != NULL && id != NULL)
	{
		retorno = 0;
		*id = this->id;
	}
	return retorno;
}

/**
 * \brief Valida, convierte y asigna un id a un empleado
 *
 * \param this Puntero al bloque de bytes asignado al empleado que se desea setear.
 * \param id Puntero a cadena donde se encuentra el valor de ID a ser asignado.
 * \return Retorna 0 (ÉXITO) si se logró asignar, -1 (ERROR) si no.
 *
 */
int employee_setIdTxt(Employee* this,char* id)
{
	int retorno = -1;
	if(this != NULL && id != NULL)
	{
		if(isValidId(id,10))
		{
			retorno = 0;
			this->id = atoi(id);
		}
	}
	return retorno;
}

/**
 * \brief Obtiene el id de un empleado en modo texto
 *
 * \param this Puntero al bloque de bytes asignado al empleado que se desea leer.
 * \param id Puntero a espacio de memoria donde se guardará el valor de ID leído.
 * \return Retorna 0 (ÉXITO) si se logró leer, -1 (ERROR) si no.
 *
 */
int employee_getIdTxt(Employee* this,char* id)
{
	int retorno = -1;
	if(this != NULL && id != NULL)
	{
		retorno = 0;
		sprintf(id,"%d",this->id);
	}
	return retorno;
}

/**
 * \brief Valida y asigna un nombre a un empleado
 *
 * \param this Puntero al bloque de bytes asignado al empleado que se desea setear.
 * \param nombre Puntero a cadena donde se guarda el nombre a ser asignado.
 * \return Retorna 0 (ÉXITO) si se logró asignar, -1 (ERROR) si no.
 *
 */
int employee_setNombre(Employee* this,char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL)
	{
		if(isValidNombre(nombre,NOMBRE_LEN))
		{
			retorno = 0;
			strncpy(this->nombre,nombre,NOMBRE_LEN);
		}
	}
	return retorno;
}

/**
 * \brief Obtiene el nombre de un empleado
 *
 * \param this Puntero al bloque de bytes asignado al empleado que se desea leer.
 * \param nombre Puntero a espacio de memoria donde se guardará el nombre leído.
 * \return Retorna 0 (ÉXITO) si se logró leer, -1 (ERROR) si no.
 *
 */
int employee_getNombre(Employee* this,char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL)
	{
		retorno = 0;
		strncpy(nombre,this->nombre,NOMBRE_LEN);
	}
	return retorno;
}

/**
 * \brief Valida y asigna la cantidad de horas trabajadas a un empleado
 *
 * \param this Puntero al bloque de bytes asignado al empleado que se desea setear.
 * \param horasTrabajadas Valor de horas trabajadas a ser asignado.
 * \return Retorna 0 (ÉXITO) si se logró asignar, -1 (ERROR) si no.
 *
 */
int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && horasTrabajadas > 0)
	{
		retorno = 0;
		this->horasTrabajadas = horasTrabajadas;
	}
	return retorno;
}

/**
 * \brief Obtiene la cantidad de horas trabajadas de un empleado
 *
 * \param this Puntero al bloque de bytes asignado al empleado que se desea leer.
 * \param horasTrabajadas Puntero a espacio de memoria donde se guardará el valor de horasTrabajadas leído.
 * \return Retorna 0 (ÉXITO) si se logró leer, -1 (ERROR) si no.
 *
 */
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && horasTrabajadas != NULL)
	{
		retorno = 0;
		*horasTrabajadas = this->horasTrabajadas;
	}
	return retorno;
}

/**
 * \brief Valida, convierte y asigna la cantidad de horas trabajadas a un empleado en modo texto.
 *
 * \param this Puntero al bloque de bytes asignado al empleado que se desea setear.
 * \param horasTrabajadas Puntero a cadena donde se encuentra el valor de horasTrabajadas a ser asignado.
 * \return Retorna 0 (ÉXITO) si se logró asignar, -1 (ERROR) si no.
 *
 */
int employee_setHorasTrabajadasTxt(Employee* this,char* horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && horasTrabajadas != NULL)
	{
		if(isValidHoras(horasTrabajadas,4))
		{
			retorno = 0;
			this->horasTrabajadas = atoi(horasTrabajadas);
		}
	}
	return retorno;
}

/**
 * \brief Obtiene la cantidad de horas trabajadas de un empleado en modo texto
 *
 * \param this Puntero al bloque de bytes asignado al empleado que se desea leer.
 * \param horasTrabajadas Puntero a cadena donde se guardará la cantidad de horas trabajadas leído.
 * \return Retorna 0 (ÉXITO) si se logró leer, -1 (ERROR) si no.
 *
 */
int employee_getHorasTrabajadasTxt(Employee* this,char* horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && horasTrabajadas != NULL)
	{
		retorno = 0;
		sprintf(horasTrabajadas,"%d",this->horasTrabajadas);
	}
	return retorno;
}

/**
 * \brief Valida y asigna el sueldo a un empleado
 *
 * \param this Puntero al bloque de bytes asignado al empleado que se desea setear.
 * \param sueldo Valor de sueldo a ser asignado a un empleado.
 * \return Retorna 0 (ÉXITO) si se logró asignar, -1 (ERROR) si no.
 *
 */
int employee_setSueldo(Employee* this,int sueldo)
{
	int retorno = -1;
	if(this != NULL && sueldo > 0)
	{
		retorno = 0;
		this->sueldo = sueldo;
	}
	return retorno;
}

/**
 * \brief Obtiene el sueldo de un empleado
 *
 * \param this Puntero al bloque de bytes asignado al empleado que se desea leer.
 * \param sueldo Puntero a espacio de memoria donde se guardará el valor del sueldo leído.
 * \return Retorna 0 (ÉXITO) si se logró leer, -1 (ERROR) si no.
 *
 */
int employee_getSueldo(Employee* this,int* sueldo)
{
	int retorno = -1;
	if(this != NULL && sueldo != NULL)
	{
		retorno = 0;
		*sueldo = this->sueldo;
	}
	return retorno;
}

/**
 * \brief Valida, convierte y asigna el sueldo a un empleado en modo texto.
 *
 * \param this Puntero al bloque de bytes asignado al empleado que se desea setear.
 * \param sueldo Puntero a cadena donde se encuentra el valor de sueldo a ser asignado.
 * \return Retorna 0 (ÉXITO) si se logró asignar, -1 (ERROR) si no.
 *
 */
int employee_setSueldoTxt(Employee* this,char* sueldo)
{
	int retorno = -1;
	if(this != NULL && sueldo != NULL)
	{
		if(isValidSueldo(sueldo,10))
		{
			retorno = 0;
			this->sueldo = atoi(sueldo);
		}
	}
	return retorno;
}

/**
 * \brief Obtiene el sueldo de un empleado en modo texto
 *
 * \param this Puntero al bloque de bytes asignado al empleado que se desea leer.
 * \param sueldo Puntero a cadena donde se guardará el sueldo leído.
 * \return Retorna 0 (ÉXITO) si se logró leer, -1 (ERROR) si no.
 *
 */
int employee_getSueldoTxt(Employee* this,char* sueldo)
{
	int retorno = -1;
	if(this != NULL && sueldo != NULL)
	{
		retorno = 0;
		sprintf(sueldo,"%d",this->sueldo);
	}
	return retorno;
}

/*****************************************************************************************************************/

/**
 * \brief esNumerica Verifica si la cadena ingresada es un id válido
 * \param cadena Puntero a espacio de memoria donde guarda la cadena de caracteres a ser analizada
 * \param limite Tamaño de la cadena a ser analizada
 * \return Retorna 1 (vardadero) si la cadena es numerica y 0 (falso) si no lo es
 *
 */
static int isValidId(char* cadena, int limite)
{
	int retorno = -1;
	int i;
	if(cadena != NULL && limite > 0)
	{
		retorno = 1;
		for(i=0; cadena[i] != '\0' && i < limite; i++)
		{
			if(cadena[i] < '0'||cadena[i] > '9')
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Verifica si la cadena ingresada es un nombre válido
 * \param cadena Cadena de caracteres a ser analizada
 * \param longitud Tamaño del array a ser analizado
 * \return Retorna 1 (verdadero) si la cadena es nombre, 0 (falso) si no lo es y -1 en caso de error
 *
 */
static int isValidNombre(char* cadena,int longitud)
{
	int i;
	int retorno = -1;

	if(cadena != NULL && longitud > 0)
	{
		for(i=0 ; cadena[i] != '\0' && i < longitud; i++)
		{
			retorno = 1;
			if( i == 0 &&
				(cadena[i] < 'A' || cadena[i] > 'Z') &&
				cadena[i] != 'Ñ' )
			{
				retorno = 0;
				break;
			}
			if( i > 0 &&
				(cadena[i] < 'a' || cadena[i] > 'z') &&
				cadena[i] != 'ñ' &&
				cadena[i] != 'á' &&
				cadena[i] != 'é' &&
				cadena[i] != 'í' &&
				cadena[i] != 'ó' &&
				cadena[i] != 'ú' &&
				cadena[i] != '´' &&
				cadena[i] != '-' &&
				cadena[i] != ' ' )
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Verifica si la cadena ingresada es una hora válida
 * \param cadena Puntero a espacio de memoria donde guarda la cadena de caracteres a ser analizada
 * \param limite Tamaño de la cadena a ser analizada
 * \return Retorna 1 (vardadero) si la cadena es numerica y 0 (falso) si no lo es
 *
 */
static int isValidHoras(char* cadena, int limite)
{
	int retorno = -1;
	int i;
	if(cadena != NULL && limite > 0)
	{
		retorno = 1;
		for(i=0; cadena[i] != '\0' && i < limite; i++)
		{
			if(cadena[i] < '0'||cadena[i] > '9')
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Verifica si la cadena ingresada es un sueldo válido
 * \param cadena Puntero a espacio de memoria donde guarda la cadena de caracteres a ser analizada
 * \param limite Tamaño de la cadena a ser analizada
 * \return Retorna 1 (vardadero) si la cadena es numerica y 0 (falso) si no lo es
 *
 */
static int isValidSueldo(char* cadena, int limite)
{
	int retorno = -1;
	int i;
	if(cadena != NULL && limite > 0)
	{
		retorno = 1;
		for(i=0; cadena[i] != '\0' && i < limite; i++)
		{
			if(cadena[i] < '0'||cadena[i] > '9')
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/*****************************************************************************************************************/

/**
 * \brief Ordena empleados por id.
 *
 * \param itemA Puntero a elemento que se quiere comparar.
 * \param itemB Puntero a elemento que se quiere comparar.
 * \return Retorna 1 si itemA es mayor a itemB, -1 si itemA es menor a itemB, 0 si son iguales o si los parámetros recibidos son NULL.
 *
 */
int employee_sortById(void* itemA,void* itemB)
{
	int respuesta = 0;
	Employee* pEmpleadoA;
	Employee* pEmpleadoB;
	int idA;
	int idB;
	if(itemA != NULL && itemB != NULL)
	{
		pEmpleadoA = (Employee*)itemA;
		pEmpleadoB = (Employee*)itemB;
		if( !employee_getId(pEmpleadoA,&idA) &&
			!employee_getId(pEmpleadoB,&idB) )
		{
			if(idA > idB)
			{
				respuesta = 1;
			}
			else if(idA < idB)
			{
				respuesta = -1;
			}
		}
	}
	return respuesta;
}

/**
 * \brief Ordena empleados por nombre.
 *
 * \param itemA Puntero a elemento que se quiere comparar.
 * \param itemB Puntero a elemento que se quiere comparar.
 * \return Retorna 1 si itemA es mayor a itemB, -1 si itemA es menor a itemB, 0 si son iguales o si los parámetros recibidos son NULL.
 *
 */
int employee_sortByNombre(void* itemA,void* itemB)
{
	int respuesta = 0;
	Employee* pEmpleadoA;
	Employee* pEmpleadoB;
	char nombreEmpleadoA[NOMBRE_LEN];
	char nombreEmpleadoB[NOMBRE_LEN];
	int auxiliarCmp;
	if(itemA != NULL && itemB != NULL)
	{
		pEmpleadoA = (Employee*)itemA;
		pEmpleadoB = (Employee*)itemB;
		if( !employee_getNombre(pEmpleadoA,nombreEmpleadoA) &&
			!employee_getNombre(pEmpleadoB,nombreEmpleadoB) )
		{
			auxiliarCmp = strncmp(nombreEmpleadoA,nombreEmpleadoB,NOMBRE_LEN);
			if(auxiliarCmp > 0)
			{
				respuesta = 1;
			}
			else if(auxiliarCmp < 0)
			{
				respuesta = -1;
			}
		}
	}
	return respuesta;
}

/**
 * \brief Ordena empleados por horas trabajadas.
 *
 * \param itemA Puntero a elemento que se quiere comparar.
 * \param itemB Puntero a elemento que se quiere comparar.
 * \return Retorna 1 si itemA es mayor a itemB, -1 si itemA es menor a itemB, 0 si son iguales o si los parámetros recibidos son NULL.
 *
 */
int employee_sortByHorasTrabajadas(void* itemA,void* itemB)
{
	int respuesta = 0;
	Employee* pEmpleadoA;
	Employee* pEmpleadoB;
	int horasTrabajadasA;
	int horasTrabajadasB;
	if(itemA != NULL && itemB != NULL)
	{
		pEmpleadoA = (Employee*)itemA;
		pEmpleadoB = (Employee*)itemB;
		if( !employee_getHorasTrabajadas(pEmpleadoA,&horasTrabajadasA) &&
			!employee_getHorasTrabajadas(pEmpleadoB,&horasTrabajadasB) )
		{
			if(horasTrabajadasA > horasTrabajadasB)
			{
				respuesta = 1;
			}
			else if(horasTrabajadasA < horasTrabajadasB)
			{
				respuesta = -1;
			}
		}
	}
	return respuesta;
}

/**
 * \brief Ordena empleados por sueldo.
 *
 * \param itemA Puntero a elemento que se quiere comparar.
 * \param itemB Puntero a elemento que se quiere comparar.
 * \return Retorna 1 si itemA es mayor a itemB, -1 si itemA es menor a itemB, 0 si son iguales o si los parámetros recibidos son NULL.
 *
 */
int employee_sortBySueldo(void* itemA,void* itemB)
{
	int respuesta = 0;
	Employee* pEmpleadoA;
	Employee* pEmpleadoB;
	int sueldoA;
	int sueldoB;
	if(itemA != NULL && itemB != NULL)
	{
		pEmpleadoA = (Employee*)itemA;
		pEmpleadoB = (Employee*)itemB;
		if( !employee_getSueldo(pEmpleadoA,&sueldoA) &&
			!employee_getSueldo(pEmpleadoB,&sueldoB) )
		{
			if(sueldoA > sueldoB)
			{
				respuesta = 1;
			}
			else if(sueldoA < sueldoB)
			{
				respuesta = -1;
			}
		}
	}
	return respuesta;
}
