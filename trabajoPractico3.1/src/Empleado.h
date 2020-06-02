/*
 * Empleado.h
 *
 *  Created on: 30 may. 2020
 *      Author: Usuario
 */

#ifndef EMPLEADO_H_
#define EMPLEADO_H_
#define NOMBRE_LEN 128

struct empleado
{
	int id;
	char nombre[NOMBRE_LEN];
	int horasTrabajadas;
	int sueldo;
}typedef Empleado;

Empleado* empleado_new(void);
Empleado* empleado_newParametros(int id,char* nombre,int horasTrabajadas,int sueldo);
Empleado* empleado_newParametrosTxt(char* id,char* nombre,char* horasTrabajadas,char* sueldo);
void empleado_delete(Empleado* this);
int empleado_setId(Empleado* this,int id);
int empleado_getId(Empleado* this,int* id);
int empleado_setIdTxt(Empleado* this,char* id);
int empleado_getIdTxt(Empleado* this,char* id);
int empleado_setNombre(Empleado* this,char* nombre);
int empleado_getNombre(Empleado* this,char* nombre);
int empleado_setHorasTrabajadas(Empleado* this,int horasTrabajadas);
int empleado_getHorasTrabajadas(Empleado* this,int* horasTrabajadas);
int empleado_setHorasTrabajadasTxt(Empleado* this,char* horasTrabajadas);
int empleado_getHorasTrabajadasTxt(Empleado* this,char* horasTrabajadas);
int empleado_setSueldo(Empleado* this,int sueldo);
int empleado_getSueldo(Empleado* this,int* sueldo);
int empleado_setSueldoTxt(Empleado* this,char* sueldo);
int empleado_getSueldoTxt(Empleado* this,char* sueldo);

/*****************************************************************************************************************/

int empleado_initArray(Empleado* arrayPunteros[],int limite);
int empleado_agregarEmpleadoArray(Empleado* arrayPunteros[],int limite,int id,char* nombre,int horasTrabajadas,int sueldo);
int empleado_parseEmpleado(Empleado* arrayPunteros[],int limite,char* pathArchivo,int* proximoId);
int empleado_agregarEmpleadoTxtArray(Empleado* arrayPunteros[],int limite,char* id,char* nombre,char* horasTrabajadas,char* sueldo);
int empleado_buscarLibreArray(Empleado* arrayPunteros[],int limite);
int empleado_imprimirArray(Empleado* arrayPunteros[],int limite);
int empleado_guardarArrayEnArchivo(Empleado* arrayPunteros[],int limite,char* pathArchivo);
int empleado_buscarPorIdArray(Empleado* arrayPunteros[],int limite, int idBuscado);
int empleado_eliminarIndiceEnArray(Empleado* arrayPunteros[],int limite, int indiceBuscado);
int empleado_ordenarArray(Empleado* arrayPunteros[],int limite);
int empleado_guardarArrayEnArchivoBinario(Empleado* arrayPunteros[],int limite,char* pathArchivo);
//int empleado_guardarlecturaArchivoArrayBinario(Empleado* arrayPunteros[],int limite,char* pathArchivo,int* proximoId);
int empleado_parseEmpleadoBinario(Empleado* arrayPunteros[],int limite,char* pathArchivo,int* proximoId);

#endif /* EMPLEADO_H_ */
