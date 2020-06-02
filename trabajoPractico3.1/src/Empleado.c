/*
 * Empleado.c
 *
 *  Created on: 30 may. 2020
 *      Author: Usuario
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "Empleado.h"

static int isValidId(char* cadena, int limite);
static int isValidNombre(char* cadena,int longitud);
static int isValidHoras(char* cadena, int limite);
static int isValidSueldo(char* cadena, int limite);

/**
 *
 *
 */
Empleado* empleado_new(void)
{
	Empleado* punteroAuxiliar = NULL;
	punteroAuxiliar = (Empleado*) malloc(sizeof(Empleado));
	return punteroAuxiliar;
}
/**
 *
 *
 */
Empleado* empleado_newParametros(int id,char* nombre,int horasTrabajadas,int sueldo)
{
	Empleado* this = NULL;
	this = empleado_new();
	if(this != NULL && nombre != NULL)
	{
		if(	empleado_setId(this,id) == -1 ||
			empleado_setNombre(this,nombre) == -1 ||
			empleado_setHorasTrabajadas(this,horasTrabajadas) == -1 ||
			empleado_setSueldo(this,sueldo) == -1 )
		{
			empleado_delete(this);
			this = NULL;
		}
	}
	return this;
}
/**
 *
 *
 */
Empleado* empleado_newParametrosTxt(char* id,char* nombre,char* horasTrabajadas,char* sueldo)
{
	Empleado* this = NULL;
	this = empleado_new();
	if(this != NULL && id != NULL && nombre != NULL && horasTrabajadas != NULL && sueldo != NULL)
	{
		if(	empleado_setIdTxt(this,id) == -1 ||
			empleado_setNombre(this,nombre) == -1 ||
			empleado_setHorasTrabajadasTxt(this,horasTrabajadas) == -1 ||
			empleado_setSueldoTxt(this,sueldo) == -1 )
		{
			empleado_delete(this);
			this = NULL;
		}
	}
	return this;
}
/**
 *
 *
 */
void empleado_delete(Empleado* this)
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
int empleado_setId(Empleado* this,int id)
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
int empleado_getId(Empleado* this,int* id)
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
int empleado_setIdTxt(Empleado* this,char* id)
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
int empleado_getIdTxt(Empleado* this,char* id)
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
int empleado_setNombre(Empleado* this,char* nombre)
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
int empleado_getNombre(Empleado* this,char* nombre)
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
int empleado_setHorasTrabajadas(Empleado* this,int horasTrabajadas)
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
int empleado_getHorasTrabajadas(Empleado* this,int* horasTrabajadas)
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
int empleado_setHorasTrabajadasTxt(Empleado* this,char* horasTrabajadas)
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
int empleado_getHorasTrabajadasTxt(Empleado* this,char* horasTrabajadas)
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
int empleado_setSueldo(Empleado* this,int sueldo)
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
int empleado_getSueldo(Empleado* this,int* sueldo)
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
int empleado_setSueldoTxt(Empleado* this,char* sueldo)
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
int empleado_getSueldoTxt(Empleado* this,char* sueldo)
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
int empleado_initArray(Empleado* arrayPunteros[],int limite)
{
	int retorno = -1;
	int i;
	if(arrayPunteros != NULL && limite > 0)
	{
		retorno = 0;
		for(i=0; i<limite; i++)
		{
			arrayPunteros[i] = NULL;
		}
	}
	return retorno;
}
/**
 *
 *
 */
int empleado_agregarEmpleadoArray(Empleado* arrayPunteros[],int limite,int id,char* nombre,int horasTrabajadas,int sueldo)
{
	int retorno = -1; //valor de error si los parámetros no son válidos
	int indiceLibre;
	Empleado* pAuxiliarEmpleado;
	if(arrayPunteros != NULL && limite > 0 && id >= 0 && nombre != NULL && horasTrabajadas > 0 && sueldo > 0)
	{
		retorno = -2; //valor de error si no hay indice libre
		indiceLibre = empleado_buscarLibreArray(arrayPunteros,limite);
		if(indiceLibre >= 0)
		{
			retorno = -3; //valor de error si no se pudo agregar empleado
			pAuxiliarEmpleado = empleado_newParametros(id,nombre,horasTrabajadas,sueldo);
			if(pAuxiliarEmpleado != NULL)
			{
				arrayPunteros[indiceLibre] = pAuxiliarEmpleado;
				retorno = indiceLibre;
			}
		}
	}
	return retorno;
}
/**
 *
 *
 */
int empleado_agregarEmpleadoTxtArray(Empleado* arrayPunteros[],int limite,char* id,char* nombre,char* horasTrabajadas,char* sueldo)
{
	int retorno = -1;
	int indiceLibre;
	Empleado* pAuxiliarEmpleado;
	if(arrayPunteros != NULL && limite > 0 && id != NULL && nombre != NULL && horasTrabajadas != NULL && sueldo != NULL)
	{
		indiceLibre = empleado_buscarLibreArray(arrayPunteros,limite);
		if(indiceLibre >= 0)
		{
			pAuxiliarEmpleado = empleado_newParametrosTxt(id,nombre,horasTrabajadas,sueldo);
			if(pAuxiliarEmpleado != NULL)
			{
				arrayPunteros[indiceLibre] = pAuxiliarEmpleado;
				retorno = indiceLibre;
			}
		}
	}
	return retorno;
}
/**
 *
 *
 */
int empleado_buscarLibreArray(Empleado* arrayPunteros[],int limite)
{
	int retorno = -1;
	int i;
	if(arrayPunteros != NULL && limite > 0)
	{
		retorno = -2;
		for(i=0; i<limite; i++)
		{
			if(arrayPunteros[i] == NULL)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}
/**
 *
 *
 */
int empleado_buscarPorIdArray(Empleado* arrayPunteros[],int limite, int idBuscado)
{
	int retorno = -1; //valor de retorno si los parámetros no son válidos
	int i;
	if(arrayPunteros != NULL && limite > 0 && idBuscado >= 0)
	{
		retorno = -2; //valor de retorno si no existe el id buscado
		for(i=0; i<limite; i++)
		{
			if( arrayPunteros[i] != NULL &&
				arrayPunteros[i]->id == idBuscado )
			{
				retorno = i; //valor de retorno si encuentra id
				break;
			}
		}
	}
	return retorno;
}
/**
 *
 *
 */
int empleado_imprimirArray(Empleado* arrayPunteros[],int limite)
{
	int retorno = -1;
	int i;
	if(arrayPunteros != NULL && limite > 0)
	{
		printf("\n-----LISTA EMPLEADOS-----\n");
		for(i=0; i<limite; i++)
		{
			if(arrayPunteros[i] != NULL)
			{
				retorno = 0;
				printf("\nDir: %p - ID: %d - Nombre: %s - Horas trabajadas: %d - Sueldo: %d\n", arrayPunteros[i],
																								arrayPunteros[i]->id,
																								arrayPunteros[i]->nombre,
																								arrayPunteros[i]->horasTrabajadas,
																								arrayPunteros[i]->sueldo);
			}
		}
	}
	return retorno;
}
/**
 *
 *
 */
int empleado_eliminarIndiceEnArray(Empleado* arrayPunteros[],int limite, int indiceBuscado)
{
	int retorno = -1;
	if(arrayPunteros != NULL && limite >= 0 && indiceBuscado >= 0 && indiceBuscado < limite && arrayPunteros[indiceBuscado] != NULL )
	{
		retorno = 0;
		empleado_delete(arrayPunteros[indiceBuscado]);
		arrayPunteros[indiceBuscado] = NULL;
	}
	return retorno;
}
/**
 *
 *
 */
int empleado_ordenarArray(Empleado* arrayPunteros[],int limite)
{
	int retorno = -1;
	int i;
	int flagSwap;
	Empleado* pAuxiliarEmpleado;
	if(arrayPunteros != NULL && limite > 0)
	{
		retorno = 0;
		do
		{
			flagSwap = 0;
			for(i=0; i<limite-1; i++)
			{

				if(	arrayPunteros[i] != NULL &&
					arrayPunteros[i+1] != NULL &&
					strncmp(arrayPunteros[i]->nombre,arrayPunteros[i+1]->nombre,NOMBRE_LEN) > 0)
				{
					pAuxiliarEmpleado = arrayPunteros[i];
					arrayPunteros[i] = arrayPunteros[i+1];
					arrayPunteros[i+1] = pAuxiliarEmpleado;
					flagSwap = 1;
				}
			}
		}while(flagSwap);
	}
	return retorno;
}
/**
 *
 *
 */
int empleado_parseEmpleado(Empleado* arrayPunteros[],int limite,char* pathArchivo,int* proximoId)
{
	int retorno = -1;	//valor de retorno si los parametros no son válidos
	FILE* fpArchivo;
	char auxiliarId[4096];
	char auxiliarNombre[4096];
	char auxiliarHorasTrabajadas[4096];
	char auxiliarSueldo[4096];
	int empleadosLeidos = 0;
	if(arrayPunteros != NULL && limite > 0 && pathArchivo != NULL)
	{
		retorno = -2;	//valor de retorno si hubo error al abrir el archivo
		fpArchivo = fopen(pathArchivo,"r");
		if(fpArchivo != NULL)
		{
			//parser
			do
			{
				if(fscanf(fpArchivo,"%[^,],%[^,],%[^,],%[^\n]\n",auxiliarId,auxiliarNombre,auxiliarHorasTrabajadas,auxiliarSueldo) == 4)
				{
					if(empleado_agregarEmpleadoArray(arrayPunteros,limite,atoi(auxiliarId),auxiliarNombre,atoi(auxiliarHorasTrabajadas),atoi(auxiliarSueldo)) >= 0)
					{
						empleadosLeidos++;
						if(atoi(auxiliarId) >= *proximoId)
						{
							*proximoId = atoi(auxiliarId) + 1;
						}
					}
					else
					{
						printf("\nERROR. NO SE PUDO AGREGAR EMPLEADO\n");
					}
				}
				else
				{
					break;
				}
			}while(!feof(fpArchivo));
			fclose(fpArchivo);
			retorno = empleadosLeidos;
		}
	}
	return retorno;
}
/**
 *
 *
 */
int empleado_guardarArrayEnArchivo(Empleado* arrayPunteros[],int limite,char* pathArchivo)
{
	int retorno = -1;
	int i;
	FILE* fpArchivo;
	int auxiliarId;
	char auxiliarNombre[NOMBRE_LEN];
	int auxiliarHorasTrabajadas;
	int auxiliarSueldo;
	if(arrayPunteros != NULL && limite > 0 && pathArchivo != NULL)
	{
		fpArchivo = fopen(pathArchivo,"w");
		if(fpArchivo != NULL)
		{
			retorno = 0;
			for(i=0; i<limite; i++)
			{
				if(arrayPunteros[i] != NULL)
				{
					if(	!empleado_getId(arrayPunteros[i],&auxiliarId) &&
						!empleado_getNombre(arrayPunteros[i],auxiliarNombre) &&
						!empleado_getHorasTrabajadas(arrayPunteros[i],&auxiliarHorasTrabajadas) &&
						!empleado_getSueldo(arrayPunteros[i],&auxiliarSueldo) )
					{
						fprintf(fpArchivo,"%d,%s,%d,%d\n",auxiliarId,auxiliarNombre,auxiliarHorasTrabajadas,auxiliarSueldo);
					}
				}
			}
			fclose(fpArchivo);
		}
		else
		{
			printf("\nERROR AL ABRIR ARCHIVO.\n");
		}
	}
	return retorno;
}
/**
 *
 *
 */
int empleado_parseEmpleadoBinario(Empleado* arrayPunteros[],int limite,char* pathArchivo,int* proximoId)
{
	int retorno = -1;	//valor de retorno si los parametros no son válidos
	FILE* fpArchivo;
	Empleado auxiliarEmpleado;
	int empleadosLeidos = 0;
	if(arrayPunteros != NULL && limite > 0 && pathArchivo != NULL)
	{
		retorno = -2;	//valor de retorno si hubo error al abrir el archivo
		fpArchivo = fopen(pathArchivo,"r");
		if(fpArchivo != NULL)
		{
			do
			{
				if(fread(&auxiliarEmpleado,sizeof(Empleado),1,fpArchivo) == 1)
				{
					if(empleado_agregarEmpleadoArray(arrayPunteros,limite,auxiliarEmpleado.id,auxiliarEmpleado.nombre,auxiliarEmpleado.horasTrabajadas,auxiliarEmpleado.sueldo) >= 0)
					{
						empleadosLeidos++;
						if(auxiliarEmpleado.id >= *proximoId)
						{
							*proximoId = auxiliarEmpleado.id + 1;
						}
					}
					else
					{
						printf("\nERROR. NO SE PUDO AGREGAR EMPLEADO\n");
					}
				}
				else
				{
					break;
				}
			}while(!feof(fpArchivo));
			fclose(fpArchivo);
			retorno = empleadosLeidos;	//valor de retorno que indica cantidad de empleados leídos
		}
	}
	return retorno;
}
/**
 *
 *
 */
int empleado_guardarArrayEnArchivoBinario(Empleado* arrayPunteros[],int limite,char* pathArchivo)
{
	int retorno = -1;
	int i;
	FILE* fpArchivo;
	if(arrayPunteros != NULL && limite > 0 && pathArchivo != NULL)
	{
		fpArchivo = fopen(pathArchivo,"wb");
		if(fpArchivo != NULL)
		{
			retorno = 0;
			for(i=0; i<limite; i++)
			{
				if(arrayPunteros[i] != NULL)
				{
					retorno = fwrite(arrayPunteros[i],sizeof(Empleado),1,fpArchivo);
				}
			}
			fclose(fpArchivo);
		}
		else
		{
			printf("\nERROR AL ABRIR EL ARCHIVO.\n");
		}
	}
	return retorno;
}
