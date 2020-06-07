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
 *
 *
 */
Employee* employee_new(void)
{
	Employee* punteroAuxiliar = NULL;
	punteroAuxiliar = (Employee*) malloc(sizeof(Employee));
	return punteroAuxiliar;
}

/**
 *
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
 *
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
 *
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
 *
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
 *
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
 *
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
 *
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
 *
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
 *
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
 *
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
 *
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
 *
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
 *
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
 *
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
 *
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
 *
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
 *
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
				cadena[i] != '´' )
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
 *
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
