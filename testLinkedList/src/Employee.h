/*
 * Employee.h
 *
 *  Created on: 20 jun. 2020
 *      Author: Usuario
 */

#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#include "LinkedList.h"
#define NOMBRE_LEN 128

typedef struct
{
    int id;
    char nombre[NOMBRE_LEN];
    int horasTrabajadas;
    int sueldo;
}Employee;

Employee* employee_new();
Employee* employee_newParametrosTxt(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* sueldoStr);
Employee* employee_newParametros(int id,char* nombre,int horasTrabajadas,int sueldo);
void employee_delete();

int employee_setId(Employee* this,int id);
int employee_getId(Employee* this,int* id);

int employee_setIdTxt(Employee* this,char* id);
int employee_getIdTxt(Employee* this,char* id);

int employee_setNombre(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);

int employee_setHorasTrabajadasTxt(Employee* this,char* horasTrabajadas);
int employee_getHorasTrabajadasTxt(Employee* this,char* horasTrabajadas);

int employee_setSueldo(Employee* this,int sueldo);
int employee_getSueldo(Employee* this,int* sueldo);

int employee_setSueldoTxt(Employee* this,char* sueldo);
int employee_getSueldoTxt(Employee* this,char* sueldo);

/********************************************************************************/

int employee_findEmployeeById(LinkedList* pArrayListEmployee,Employee** pEmpleado,int proximoId);
int employee_requestEmployeeData(char* nombre,int* horasTrabajadas,int* sueldo);
int employee_editEmployeeData(Employee* pEmpleado, int (*pFuncRequestEmployeeData)(char [], int* , int* ));
int employee_sortById(void* itemA,void* itemB);
int employee_sortByNombre(void* itemA,void* itemB);
int employee_sortByHorasTrabajadas(void* itemA,void* itemB);
int employee_sortBySueldo(void* itemA,void* itemB);
/*
============================================================================
					NUEVAS FUNCIONES DE EMPLOYEE
============================================================================
*/
int employee_printEmployee(void* pElement); //NUEVO
int employee_initMemberSueldo(void* pElement); //NUEVO
int employee_initMemberHorasTrabajadas(void* pElement); //NUEVO
int employee_calcularSueldo(void* pElement); //NUEVO
int employee_trabajaMasDe100Horas(void* pElement); //NUEVO
int employee_acumularSueldo(void* pElement, int sueldoAcumulado); //NUEVO
int employee_compararSueldoPorMayor(void* pElement, int mayor, int index); //NUEVO

#endif /* EMPLOYEE_H_ */
