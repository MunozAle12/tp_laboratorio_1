/*
 * Controller.h
 *
 *  Created on: 20 jun. 2020
 *      Author: Usuario
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

int controller_loadFromText(char* path,LinkedList* pArrayListEmployee);
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee);
int controller_addEmployee(LinkedList* pArrayListEmployee,int id);
int controller_editEmployee(LinkedList* pArrayListEmployee,int proximoId);
int controller_removeEmployee(LinkedList* pArrayListEmployee,int proximoId);
int controller_ListEmployee(LinkedList* pArrayListEmployee);
int controller_sortEmployee(LinkedList* pArrayListEmployee);
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee);
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee);
/*
============================================================================
					NUEVAS FUNCIONES DE CONTROLLER
============================================================================
*/
int controller_reportingEmployeesWithMoreThan100WorkingHours(LinkedList* pArrayListEmployee); //NUEVO
int controller_InitEmployeeDataOfList(LinkedList* pArrayListEmployee); //NUEVO
int controller_calculateEmployeeSalary(LinkedList* pArrayListEmployee); //NUEVO
int controller_reportingTotalSalaryBalance(LinkedList* pArrayListEmployee); //NUEVO
int controller_informarEmpleadoConMayorSueldo(LinkedList* pArrayListEmployee); //NUEVO

#endif /* CONTROLLER_H_ */
