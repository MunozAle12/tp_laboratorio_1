/*
 ============================================================================
 Name        : trabajoPractico2.c
 Author      : Ale Mu�oz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 Enunciado:
 Una empresa requiere un sistema para administrar su n�mina de empleados. Se sabe que
 dicha n�mina bajo ninguna circunstancia superara los 1000 empleados.

 El sistema deber� tener el siguiente men� de opciones:
 1. ALTAS: Se debe permitir ingresar un empleado calculando autom�ticamente el n�mero
 	 	   de Id. El resto de los campos se le pedir� al usuario.
 2. MODIFICAR: Se ingresar� el N�mero de Id, permitiendo modificar: o Nombre o Apellido
 	 	 	   o Salario o Sector
 3. BAJA: Se ingresar� el N�mero de Id y se eliminar� el empleado del sistema.
 4. INFORMAR:
	a. Listado de los empleados ordenados alfab�ticamente por Apellido y Sector.
	b. Total y promedio de los salarios, y cu�ntos empleados superan el salario promedio.

 NOTA: Se deber� realizar el men� de opciones y las validaciones a trav�s de funciones.
 Tener en cuenta que no se podr� ingresar a los casos 2, 3 y 4; sin antes haber realizado la
 carga de alg�n empleado.
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "Empleado.h"
#include "Informes.h"
#define EMPLEADOS_LEN 1000

int main(void)
{
	setbuf(stdout,NULL);
	Empleado arrayEmpleados[EMPLEADOS_LEN];
	int opcion;
	int auxiliarIndice;
	int auxiliarId;
	int idEmpleado = 0;

	if(emp_initEmployees(arrayEmpleados,EMPLEADOS_LEN) != -1)
	{
		printf("El array de empleados se inicializ� con �xito.\n");
	}
/*
	//FORZAR ALTA DE EMPLEADOS
	emp_altaArrayDebug(arrayEmpleados,EMPLEADOS_LEN,0,&idEmpleado,"Lorenzo","Pasos",22890.86,3);
	emp_altaArrayDebug(arrayEmpleados,EMPLEADOS_LEN,1,&idEmpleado,"Eugenia","Diaz",32000.00,1);
	emp_altaArrayDebug(arrayEmpleados,EMPLEADOS_LEN,2,&idEmpleado,"Leonardo","Pasos",28200.86,3);
	emp_altaArrayDebug(arrayEmpleados,EMPLEADOS_LEN,3,&idEmpleado,"Sebasti�n","Di Fazio",31200.86,1);
	emp_altaArrayDebug(arrayEmpleados,EMPLEADOS_LEN,4,&idEmpleado,"Mat�as","Diaz",15370.86,5);
	emp_altaArrayDebug(arrayEmpleados,EMPLEADOS_LEN,5,&idEmpleado,"Ricardo","Pasos",18200.86,4);
	emp_altaArrayDebug(arrayEmpleados,EMPLEADOS_LEN,6,&idEmpleado,"Julia","Olivera",28200.86,2);
	emp_altaArrayDebug(arrayEmpleados,EMPLEADOS_LEN,7,&idEmpleado,"Sabrina","Del Solar",19500.86,4);
	emp_altaArrayDebug(arrayEmpleados,EMPLEADOS_LEN,8,&idEmpleado,"Joaqu�n","Mendez",30200.16,1);
	emp_altaArrayDebug(arrayEmpleados,EMPLEADOS_LEN,9,&idEmpleado,"Lorenzo","Olmos",25929.86,2);
*/
	do
	{
		if( !utn_getNumero(&opcion,"\nIngrese una opci�n:\n"
								    "1. Agregar empleado\n"
									"2. Modificar empleado\n"
									"3. Eliminar empleado\n"
									"4. Informar\n"
									"5. Salir\n","\nIngreso inv�lido. ",1,5,2) )
		{
			switch(opcion)
			{
				case 1:
					auxiliarIndice = emp_getEmptyIndex(arrayEmpleados,EMPLEADOS_LEN);
					if(auxiliarIndice != -1)
					{
						if(!emp_addEmployee(arrayEmpleados,EMPLEADOS_LEN,auxiliarIndice,&idEmpleado))
						{
							printf("\nEl alta de cliente fue un �xito.\n");
						}
						else
						{
							printf("\nEl alta de cliente fall�.\n");
						}
					}
					else
					{
						printf("\nNo hay lugar disponible.\n");
					}
					break;
				case 2:
					if(!emp_findLoadedEmployees(arrayEmpleados,EMPLEADOS_LEN))
					{
						if(!utn_getNumero(&auxiliarId,"Ingrese ID de empleado: \n","\nID INVALIDO. ",0,idEmpleado,2))
						{
							auxiliarIndice = emp_findEmployeeById(arrayEmpleados,EMPLEADOS_LEN,auxiliarId);
							if(auxiliarIndice != -1)
							{
								if(emp_modifyEmployee(arrayEmpleados,EMPLEADOS_LEN,auxiliarIndice) == -1)
								{
									printf("\nLa modificaci�n de dato de empleado fall�.\n");
								}
							}
							else
							{
								printf("\nNo existe empleado.\n");
							}
						}
						else
						{
							printf("\nSe acabaron sus reintentos. Ingreso incorrecto.\n");
						}
					}
					else
					{
						printf("\nDebe cargar al menos un empleado.\n");
					}
					break;
				case 3:
					if(!emp_findLoadedEmployees(arrayEmpleados,EMPLEADOS_LEN))
					{
						if(!utn_getNumero(&auxiliarId,"Ingrese ID de empleado: \n","\nID INVALIDO. ",0,idEmpleado,2))
						{
							auxiliarIndice = emp_findEmployeeById(arrayEmpleados,EMPLEADOS_LEN,auxiliarId);
							if(auxiliarIndice != -1)
							{
								if(!emp_removeEmployee(arrayEmpleados,EMPLEADOS_LEN,auxiliarIndice))
								{
									printf("\nLa baja del empleado fue un �xito.\n");
								}
								else
								{
									printf("\nLa baja del empleado fall�.\n");
								}
							}
							else
							{
								printf("\nNo existe empleado.\n");
							}
						}
						else
						{
							printf("\nSe acabaron sus reintentos. Ingreso incorrecto.\n");
						}
					}
					else
					{
						printf("\nDebe cargar al menos un empleado.\n");
					}
					break;
				case 4:
					if(!emp_findLoadedEmployees(arrayEmpleados,EMPLEADOS_LEN))
					{
						if( info_reportEmployeesList(arrayEmpleados,EMPLEADOS_LEN) == -1 )
						{
							printf("\n�ERROR!\n");
						}
						if(info_reportEmployeesSalaries(arrayEmpleados,EMPLEADOS_LEN) == -1)
						{
							printf("\n�ERROR!\n");
						}
					}
					else
					{
						printf("\nDebe cargar al menos un empleado.\n");
					}
					break;
			}
		}
	}while(opcion != 5);
	return EXIT_SUCCESS;
}
