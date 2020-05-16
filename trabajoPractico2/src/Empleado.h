/*
 * Empleado.h
 *
 *  Created on: 28 abr. 2020
 *      Author: Usuario
 */

#ifndef EMPLEADO_H_
#define EMPLEADO_H_

#define NOMBRE_LEN 51
#define APELLIDO_LEN 51

struct empleado
{
	char nombre[NOMBRE_LEN];
	char apellido[APELLIDO_LEN];
	float salario;
	int sector;
	int id;
	int isEmpty;
}typedef Empleado;

int emp_printEmployee(Empleado* pElemento);
int emp_printEmployees(Empleado* array,int limite);
int emp_initEmployees(Empleado* array,int limite);
int emp_getEmptyIndex(Empleado* array,int limite);
int emp_addEmployee(Empleado* array,int limite,int indice,int* idEmpleado);
int emp_modifyEmployee(Empleado* array,int limite,int indice);
int emp_findLoadedEmployees(Empleado* array,int limite);
int emp_findEmployeeById(Empleado* array,int limite,int valorBuscado);
int emp_removeEmployee(Empleado* array,int limite,int indice);
int emp_calculateSalary(Empleado* array,int limite,float* pSalarioTotal,float* pSalarioPromedio);
int emp_calculateEmployeesExceedAverageSalary(Empleado* array,int limite,float promedio,int* pCantidadEmpleados);

/* FUNCION PARA FORZAR ALTA DE EMPLEADOS */
int emp_altaArrayDebug(Empleado* array,int limite,int indice,int* idEmpleado,char* nombre,char* apellido,float salarioEmpleado,int sectorEmpleado);

#endif /* EMPLEADO_H_ */
