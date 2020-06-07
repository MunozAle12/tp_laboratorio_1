/*
 * utn.c
 *
 *  Created on: 30 may. 2020
 *      Author: Usuario
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int getString(char* cadena,int longitud);
static int getInt(int* pResultado);
static int esNumerica(char* cadena,int limite);
static int getFloat(float* pResultado);
static int esFlotante(char* cadena,int limite);
static int getCuit(char* pResultado,int longitud);
static int esCuit(char* cadena,int limite);
static int getNombre(char* pResultado,int longitud);
static int esNombre(char* cadena,int longitud);
static int getApellido(char* pResultado, int longitud);
static int esApellido(char* cadena,int longitud);
static int getTexto(char* pResultado,int longitud);
static int esTexto(char* cadena,int longitud);
static int getLetra(char* pResultado);
static int esLetra(char* cadena, int limite);

/**
 * \brief Guarda una lectura del archivo stdin hasta que encuentra un '\0'
 *        o hasta que haya copiado en cadena un máximo de 'longitud - 1' caracteres.
 * \param cadena Puntero al espacio de memoria donde se copiara la cadena obtenida
 * \param longitud Define el tamaño de cadena
 * \return Retorna 0 (EXITO) si se obtiene una cadena y -1 (ERROR) si no
 *
 */
static int getString(char* cadena, int longitud)
{
	int retorno=-1;
	char bufferString[4096]; // *****************************

	if(cadena != NULL && longitud > 0)
	{
		//fpurge(stdin); MacOS
		//__fpurge(stdin); Linux
		fflush(stdin); //Windows
		if(fgets(bufferString,sizeof(bufferString),stdin) != NULL) //Leo lo que se ingresa por teclado y lo guardo en un string
		{
			if(bufferString[strnlen(bufferString,sizeof(bufferString))-1] == '\n')
			{
				bufferString[strnlen(bufferString,sizeof(bufferString))-1] = '\0';
			}
			if(strnlen(bufferString,sizeof(bufferString)) <= longitud)
			{
				strncpy(cadena,bufferString,longitud);
				retorno=0;
			}
		}
	}
	return retorno;
}
/**
 * \brief utn_getNumero Solicita un número al usuario y luego de verificarlo devuelve un resultado.
 * \param pResultado Puntero al espacio de memoria donde se guardará el número verificado.
 * \param mensaje Es el mensaje a ser mostrado por pantalla.
 * \param mensajeError Es el mensaje de error a ser mostrado por pantalla.
 * \param minimo Es el número maximo del rango de valores aceptados.
 * \param maximo Es el mínimo del rango de valores a ser aceptados.
 * \param reintentos Cantidad de reintentos
 * \return Retorna 0 si se obtuvo el numero y -1 si no.
 *
 */
int utn_getNumero(int* pResultado,char* mensaje,char* mensajeError,int minimo,int maximo,int reintentos)
{
	int retorno = -1;
	int bufferInt;
	do
	{
		printf("%s",mensaje);
		if(	getInt(&bufferInt) == 0 &&
			bufferInt >= minimo &&
			bufferInt <= maximo)
		{
			retorno = 0;
			*pResultado = bufferInt;
			break;
		}
		printf("%s",mensajeError);
		reintentos--;
	}while(reintentos >= 0);

	return retorno;
}
/**
 * \brief getInt Busca y verifica si lo que se ingresó es un número entero.
 * \param pResultado Puntero al espacio de memoria donde se dejará el resultado de la función.
 * \return Retorna 0 si se obtiene un numero entero y -1 si no.
 *
 */
static int getInt(int* pResultado)
{
    int retorno=-1;
    char bufferString[50];
    if(	pResultado != NULL &&
    	getString(bufferString,sizeof(bufferString)) == 0 &&
    	esNumerica(bufferString,sizeof(bufferString)) )
	{
		retorno=0;
		*pResultado = atoi(bufferString) ;

	}
    return retorno;
}
/**
 * \brief esNumerica Verifica si la cadena ingresada es numérica.
 * \param cadena Puntero a espacio de memoria donde guarda la cadena de caracteres a ser analizada.
 * \param limite Tamaño de la cadena a ser analizada
 * \return Retorna 1 (vardadero) si la cadena es numerica y 0 (falso) si no lo es.
 *
 */
static int esNumerica(char* cadena, int limite)
{
	int retorno = -1;
	int i;
	if(cadena != NULL && limite > 0)
	{
		retorno = 1;
		for(i=0; cadena[i] != '\0' && i < limite; i++)
		{
			if( i == 0 &&
				(cadena[i] == '+' || cadena[i] == '-') )
			{
				continue;
			}
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
 * \brief Solicita un numero flotante al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param minimo Es el numero maximo del rango aceptado
 * \param maximo Es el minimo minimo del rango aceptado
 * \param reintentos Cantidad de reintentos
 * \return Retorna 0 si se obtuvo el numero flotante y -1 si no
 *
 */
int utn_getNumeroFlotante(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos)
{
	float bufferFloat;
	int retorno = -1;
	while(reintentos >= 0)
	{
		reintentos--;
		printf("%s",mensaje);
		if(getFloat(&bufferFloat) == 0)
		{
			if( bufferFloat >= minimo &&
				bufferFloat <= maximo)
			{
				*pResultado = bufferFloat;
				retorno = 0;
				break;
			}
		}
		printf("%s",mensajeError);
	}
	return retorno;
}
/**
 * \brief getFloat Busca y verifica si la cadena ingresada es un número flotante
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) si se obtiene un numero flotante y -1 (ERROR) si no
 *
 */
static int getFloat(float* pResultado)
{
    int retorno = -1;
    char buffer[64];
    if(pResultado != NULL)
    {
    	if( getString(buffer,sizeof(buffer)) == 0 &&
    		esFlotante(buffer,sizeof(buffer)) )
    	{
			*pResultado = atof(buffer);
			retorno = 0;
		}
    }
    return retorno;
}
/**
 * \brief Verifica si la cadena ingresada es válida como un número flotante
 * \param cadena Cadena de caracteres a ser analizada
 * \param limite Tamaño de la cadena a ser analizada
 * \return Retorna 1 (vardadero) si la cadena es flotante y 0 (falso) si no lo es
 *
 */
static int esFlotante(char* cadena,int limite)
{
	int i = 0;
	int retorno = 1;
	int contadorPuntos = 0;

	if(cadena != NULL && limite > 0)
	{
		for(i=0 ; cadena[i]!='\0' && i<limite; i++)
		{
			if(i==0 && (cadena[i]=='-' || cadena[i]=='+'))
			{
				continue;
			}
			if(cadena[i]<'0' || cadena[i]>'9')
			{
				if(cadena[i]=='.' && contadorPuntos==0)
				{
					contadorPuntos++;
				}
				else
				{
					retorno = 0;
					break;
				}
			}
		}
	}
	return retorno;
}
/**
 * \brief Solicita un CUIT al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del array resultado
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param reintentos Cantidad de reintentos
 * \return Retorna 0 si se obtuvo un CUIT, -1 si no
 *
 */
int utn_getCuit(char* pResultado, int longitud,char* mensaje,char* mensajeError,int reintentos)
{
	char bufferString[4096];
	int retorno = -1;
	while(reintentos >= 0)
	{
		reintentos--;
		printf("%s",mensaje);
		if( getCuit(bufferString,sizeof(bufferString)) == 0 &&
			strnlen(bufferString,sizeof(bufferString)) < longitud )
		{
			strncpy(pResultado,bufferString,longitud);
			retorno = 0;
			break;
		}
		printf("%s",mensajeError);
	}
	return retorno;
}
/**
 * \brief getCuit Busca y verifica si lo que se ingresó es un número CUIT.
 * \param pResultado Puntero al espacio de memoria donde se dejará el resultado de la función.
 * \return Retorna 0 si se obtiene un CUIT, -1 si no.
 *
 */
static int getCuit(char* pResultado,int longitud)
{
    int retorno = -1;
    char buffer[4096];

    if(pResultado != NULL)
    {
    	if(	getString(buffer,sizeof(buffer)) == 0 &&
    		esCuit(buffer,sizeof(buffer)) &&
			strnlen(buffer,sizeof(buffer)) < longitud)
    	{
    		strncpy(pResultado,buffer,longitud);
			retorno = 0;
		}
    }
    return retorno;
}
/**
 * \brief Verifica si la cadena ingresada es un CUIT
 * \param cadena Cadena de caracteres a ser analizada
 * \param limite Tamaño del array a ser analizado
 * \return Retorna 1 (verdadero) si la cadena es CUIT, 0 (falso) si no lo es y -1 en caso de error
 *
 */
static int esCuit(char* cadena,int limite)
{
	int retorno = -1;
	int i;
	if(cadena != NULL && limite > 0)
	{
		retorno = 1;
		for(i=0; cadena[i] != '\0' && i < limite; i++)
		{
			if( i == 0 &&
				cadena[i] != '2' &&
				cadena[i] != '3' )
			{
				retorno = 0;
				break;
			}
			if( i == 1 &&
				cadena[i] != '0' &&
				cadena[i] != '3' &&
				cadena[i] != '4' &&
				cadena[i] != '7' )
			{
				retorno = 0;
				break;
			}
			if(cadena[i] < '0'|| cadena[i] > '9')
			{
				retorno = 0;
				break;
			}
		}
		if(strnlen(cadena,limite) > 11)
		{
			retorno = 0;
		}
	}
	return retorno;
}
/**
 * \brief Solicita un nombre al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del array resultado
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param reintentos Cantidad de reintentos
 * \return Retorna 0 si se obtuvo el nombre y -1 si no
 *
 */
int utn_getNombre(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos)
{
	char bufferString[4096];
	int retorno = -1;
	while(reintentos >= 0)
	{
		reintentos--;
		printf("%s",mensaje);
		if( getNombre(bufferString,sizeof(bufferString)) == 0 &&
			strnlen(bufferString,sizeof(bufferString)) < longitud )
		{
			strncpy(pResultado,bufferString,longitud);
			retorno = 0;
			break;
		}
		printf("%s",mensajeError);
	}
	return retorno;
}
/**
 * \brief getNombre Busca y verifica si lo que se ingresó es un nombre.
 * \param pResultado Puntero al espacio de memoria donde se dejará el resultado de la función.
 * \param longitud Tamaño del array a ser analizado
 * \return Retorna 0 si se obtiene un nombre y -1 si no.
 *
 */
static int getNombre(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL)
    {
    	if(	getString(buffer,sizeof(buffer)) == 0 &&
    		esNombre(buffer,sizeof(buffer)) &&
			strnlen(buffer,sizeof(buffer)) < longitud)
    	{
    		strncpy(pResultado,buffer,longitud);
			retorno = 0;
		}
    }
    return retorno;
}
/**
 * \brief Verifica si la cadena ingresada es un nombre
 * \param cadena Cadena de caracteres a ser analizada
 * \param longitud Tamaño del array a ser analizado
 * \return Retorna 1 (verdadero) si la cadena es nombre, 0 (falso) si no lo es y -1 en caso de error
 *
 */
static int esNombre(char* cadena,int longitud)
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
 * \brief Solicita un apellido al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del array resultado
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param reintentos Cantidad de reintentos
 * \return Retorna 0 si se obtuvo el apellido, -1 si no
 *
 */
int utn_getApellido(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos)
{
	char bufferString[4096];
	int retorno = -1;
	while(reintentos >= 0)
	{
		reintentos--;
		printf("%s",mensaje);
		if( getApellido(bufferString,sizeof(bufferString)) == 0 &&
			strnlen(bufferString,sizeof(bufferString)) < longitud )
		{
			strncpy(pResultado,bufferString,longitud);
			retorno = 0;
			break;
		}
		printf("%s",mensajeError);
	}
	return retorno;
}
/**
 * \brief getNombre Busca y verifica si lo que se ingresó es un apellido
 * \param pResultado Puntero al espacio de memoria donde se dejará el resultado de la función
 * \param longitud Tamaño del array a ser analizado
 * \return Retorna 0 si se obtiene un apellido -1 si no
 *
 */
static int getApellido(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL)
    {
    	if(	getString(buffer,sizeof(buffer)) == 0 &&
    		esApellido(buffer,sizeof(buffer)) &&
			strnlen(buffer,sizeof(buffer)) < longitud)
    	{
    		strncpy(pResultado,buffer,longitud);
			retorno = 0;
		}
    }
    return retorno;
}
/**
 * \brief Verifica si la cadena ingresada es un apellido
 * \param cadena Cadena de caracteres a ser analizada
 * \param longitud Tamaño del array a ser analizado
 * \return Retorna 1 (verdadero) si la cadena es un apellido, 0 (falso) si no lo es y -1 en caso de error
 *
 */
static int esApellido(char* cadena,int longitud)
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
			if( (cadena[i] < 'A' || cadena[i] > 'Z') &&
				(cadena[i] < 'a' || cadena[i] > 'z') &&
				cadena[i] != 'ñ' &&
				cadena[i] != 'á' &&
				cadena[i] != 'é' &&
				cadena[i] != 'í' &&
				cadena[i] != 'ó' &&
				cadena[i] != 'ú' &&
				cadena[i] != ' ' &&
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
 * \brief Solicita un texto al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del array resultado
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param reintentos Cantidad de reintentos
 * \return Retorna 0 si se obtuvo el texto y -1 si no
 *
 */
int utn_getTexto(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos)
{
	char bufferString[4096];
	int retorno = -1;
	while(reintentos >= 0)
	{
		reintentos--;
		printf("%s",mensaje);
		if( getTexto(bufferString,sizeof(bufferString)) == 0 &&
			strnlen(bufferString,sizeof(bufferString)) < longitud )
		{
			strncpy(pResultado,bufferString,longitud);
			retorno = 0;
			break;
		}
		printf("%s",mensajeError);
	}
	return retorno;
}
/**
 * \brief getDescripcion Busca y verifica si lo que se ingresó es una Descripcion.
 * \param pResultado Puntero al espacio de memoria donde se dejará el resultado de la función.
 * \param longitud Tamaño del array a ser analizado
 * \return Retorna 0 si se obtiene un texto, -1 si no.
 *
 */
static int getTexto(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL)
    {
    	if(	getString(buffer,sizeof(buffer)) == 0 &&
    		esTexto(buffer,sizeof(buffer)) &&
			strnlen(buffer,sizeof(buffer)) < longitud )
    	{
    		strncpy(pResultado,buffer,longitud);
			retorno = 0;
		}
    }
    return retorno;
}
/**
 * \brief Verifica si la cadena ingresada es un texto
 * \param cadena Cadena de caracteres a ser analizada
 * \param longitud Tamaño del array a ser analizado
 * \return Retorna 1 (verdadero) si la cadena es un texto, 0 (falso) si no lo es y -1 en caso de error
 *
 */
static int esTexto(char* cadena,int longitud)
{
	int retorno = -1;
	int i;
	if(cadena != NULL && longitud > 0)
	{
		for(i=0 ; cadena[i] != '\0' && i < longitud; i++)
		{
			retorno = 1;
			if( (cadena[i] < '0' || cadena[i] > '9') &&
				(cadena[i] < 'A' || cadena[i] > 'Z') &&
				(cadena[i] < 'a' || cadena[i] > 'z') &&
				cadena[i] != 'á' &&
				cadena[i] != 'é' &&
				cadena[i] != 'í' &&
				cadena[i] != 'ó' &&
				cadena[i] != 'ú' &&
				cadena[i] != 'ñ' &&
				cadena[i] != 'Ñ' &&
				cadena[i] != ' ' &&
				cadena[i] != '.' &&
				cadena[i] != ',' &&
				cadena[i] != '¡' &&
				cadena[i] != '!' &&
				cadena[i] != '¿' &&
				cadena[i] != '?' &&
				cadena[i] != '(' &&
				cadena[i] != ')' &&
				cadena[i] != '"' &&
				cadena[i] != '%' &&
				cadena[i] != ';' &&
				cadena[i] != ':')
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/**
 * \brief utn_getCaracter Solicita el ingreso de una letra al usuario y luego de verificarla devuelve un resultado.
 * \param pResultado Puntero al espacio de memoria donde se guardará la letra verificada.
 * \param mensaje Es el mensaje a ser mostrado por pantalla.
 * \param mensajeError Es el mensaje de error a ser mostrado por pantalla.
 * \return Retorna 0 si se obtuvo una letra, -1 si no.
 *
 */
int utn_getLetra(char* pResultado,char* mensaje,char* mensajeError,int reintentos)
{
	char bufferLetra;
	int retorno = -1;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && reintentos >= 0)
	{
		while(reintentos>=0)
		{
			reintentos--;
			printf("%s",mensaje);
			if(getLetra(&bufferLetra) == 0)
			{
				*pResultado = bufferLetra;
				retorno = 0;
				break;
			}
			else
			{
				printf("%s",mensajeError);
			}
		}
	}
	return retorno;
}
/**
 * \brief getLetra Busca y verifica si lo que se ingresó es una letra.
 * \param pResultado Puntero al espacio de memoria donde se dejará el resultado de la función.
 * \return Retorna 0 si se obtiene una letra, -1 si no.
 *
 */
static int getLetra(char* pResultado)
{
    int retorno = -1;
    char bufferString[64];
    if(	pResultado != NULL &&
    	getString(bufferString,sizeof(bufferString)) == 0 &&
    	esLetra(bufferString,sizeof(bufferString)) )
	{
		retorno = 0;
		strncpy(pResultado,bufferString,sizeof(*pResultado));
	}
    return retorno;
}
/**
 * \brief Verifica si la cadena ingresada es una letra válida
 * \param cadena Puntero al espacio de memoria donde comienza el string a analizar
 * \param limite Tamaño del array a ser analizada
 * \return Retorna 1 si es una letra válida, 0 si no es letra, -1 si error.
 *
 */
static int esLetra(char* cadena, int limite)
{
	int retorno = -1; // ERROR
	int i;
	if(cadena != NULL && limite > 0)
	{
		retorno = 0; // FALSO
		for(i=0; i < limite && cadena[i] != '\0'; i++)
		{
			if( (cadena[i] >= 'A' && cadena[i] <= 'Z') ||
				(cadena[i] >= 'a' && cadena[i] <= 'z') )
			{
				retorno = 1; //VERDADERO
			}
		}
	}
	return retorno;
}
/**
 * \brief Inicializa un array de elementos tipo Int
 * \param array Puntero a espacio de memoria donde empieza el array a inicializar
 * \param len Tamaño del array
 * \return Retorna 0 si EXITO, -1 si ERROR.
 */
int utn_initArrayInt(int* array,int len)
{
	int retorno = -1;
	int i;
	if(array != NULL && len >0)
	{
		for(i=0; i<len; i++)
		{
			retorno = 0;
			array[i] = 0;
		}
	}
	return retorno;
}
