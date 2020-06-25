/*
 ============================================================================
 Name        : testTP4.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
============================================================================
	Menu:
	1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
	2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
	3. Alta de empleado
	4. Modificar datos de empleado
	5. Baja de empleado
	6. Listar empleados
	7. Ordenar empleados
	8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
	9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
	10. Salir
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "utn.h"

int main()
{
	setbuf(stdout,NULL);
	int option = 0;
	LinkedList* listaEmpleados = ll_newLinkedList();
	int retorno;
	int proximoId = 0;
	do
	{
		if(!utn_getNumero(&option,"\nElija una opción:\n"
									"1) Cargar datos de los empleados desde archivo 'data.csv' (modo texto)\n"
									"2) Cargar datos de los empleados desde archivo 'data.csv' (modo binario)\n"
									"3) Alta de empleado\n"
									"4) Modificar datos de empleado\n"
									"5) Baja de empleado\n"
									"6) Listar empleados\n"
									"7) Ordenar empleados\n"
									"8) Guardar datos de los empleados en archivo 'data.csv' (modo texto)\n"
									"9) Guardar datos de los empleados en archivo 'data.csv' (modo binario)\n"
									"10) Inicializar sueldo de los empleados\n"
									"11) Calcular sueldo de los empleados\n"
									"12) Informar empleados con más de 100 horas de trabajo\n"
									"13) Informar saldo total a pagar por sueldos\n"
									"14) Informar empleado con mayor sueldo\n"
									"15) Salir\n","\nOPCION INVALIDA. ",1,15,2) )
		{
			switch(option)
			{
				case 1: //1) Cargar datos de los empleados desde archivo 'data.csv' (modo texto)
					retorno = controller_loadFromText("data.csv",listaEmpleados);
					switch(retorno)
					{
						case -1:
							printf("\nERROR. LOS PARAMETROS NO SON VALIDOS O LA LISTA ESTÁ VACÍA.\n");
							break;
						case -2:
							printf("\nERROR AL ABRIR EL ARCHIVO.\n");
							break;
						case -3:
							printf("\nERROR. NO SE PUDO CREAR EMPLEADO EN MEMORIA.\n");
							break;
						case -4:
							printf("\nERROR. NO SE PUDO AGREGAR EMPLEADO A LA LISTA.\n");
							break;
						default:
							printf("\nSE CARGARON DATOS DESDE ARCHIVO CON ÉXITO.\n");
							proximoId = retorno;
					}
					break;
				case 2: //2) Cargar datos de los empleados desde archivo 'data.csv' (modo binario)
					retorno = controller_loadFromBinary("data2.csv",listaEmpleados);
					switch(retorno)
					{
						case -1:
							printf("\nERROR. LOS PARAMETROS NO SON VALIDOS O LA LISTA ESTÁ VACÍA.\n");
							break;
						case -2:
							printf("\nERROR AL ABRIR EL ARCHIVO.\n");
							break;
						case -3:
							printf("\nERROR. NO SE PUDO CREAR EMPLEADO EN MEMORIA.\n");
							break;
						default:
							printf("\nSE CARGARON DATOS DESDE ARCHIVO CON ÉXITO.\n");
							proximoId = retorno;
					}
					break;
				case 3:	//3) Alta de empleado
					retorno = controller_addEmployee(listaEmpleados,proximoId);
					switch(retorno)
					{
						case 0:
							printf("\nEMPLEADO AGREGADO CON ÉXITO.\n");
							proximoId++;
							break;
						case -1:
							printf("\nERROR. LOS PARAMETROS NO SON VÁLIDOS O LA LISTA ESTÁ VACÍA.\n");
							break;
						case -2:
							printf("\nERROR. SE INGRESÓ AL MENOS UN DATO INVALIDO.\n");
							break;
						case -3:
							printf("\nERROR. NO SE PUDO CREAR EMPLEADO EN MEMORIA.\n");
							break;
					}
					break;
				case 4: //4) Modificar datos de empleado
					retorno = controller_editEmployee(listaEmpleados,proximoId);
					switch(retorno)
					{
						case 0:
							printf("\nSE MODIFICÓ EMPLEADO CON ÉXITO.\n");
							break;
						case -1:
							printf("\nERROR. LOS PARAMETROS NO SON VÁLIDOS O LA LISTA ESTÁ VACÍA.\n");
							break;
						case -2:
							printf("\nERROR. NO SE ENCONTRÓ EMPLEADO EN LA LISTA.\n");
							break;
						case -3:
							printf("\nERROR. SE INGRESÓ AL MENOS UN DATO INVÁLIDO.\n");
							break;
						case -4:
							printf("\nERROR. NO SE LOGRÓ ASIGNAR AL MENOS UN DATO A UN CAMPO DE LA ENTIDAD.\n");
							break;
					}
					break;
				case 5: //5) Baja de empleado
					retorno = controller_removeEmployee(listaEmpleados,proximoId);
					switch(retorno)
					{
						case 0:
							printf("\nLA BAJA DEL EMPLEADO SE REALIZÓ CON ÉXITO.\n");
							break;
						case -1:
							printf("\nERROR. LOS PARAMETROS NO SON VÁLIDOS O LA LISTA ESTÁ VACÍA.\n");
							break;
						case -2:
							printf("\nERROR. NO SE ENCONTRÓ EMPLEADO EN LA LISTA.\n");
							break;
					}
					break;
				case 6: //6) Listar empleados
					retorno = controller_ListEmployee(listaEmpleados);
					switch(retorno)
					{
						case -1:
							printf("\nERROR. AL MENOS UN ELEMENTO ES NULL.\n");
							break;
						case -2:
							printf("\nERROR. LOS PARAMETROS NO SON VÁLIDOS O LA LISTA ESTÁ VACÍA.\n");
							break;
					}
					break;
				case 7: //7) Ordenar empleados
					retorno = controller_sortEmployee(listaEmpleados);
					switch(retorno)
					{
						case 0:
							controller_ListEmployee(listaEmpleados);
							break;
						case -1:
							printf("\nERROR AL ORDENAR LA LISTA.\n");
							break;
						case -2:
							printf("\nERROR. LOS PARAMETROS NO SON VÁLIDOS O LA LISTA ESTÁ VACÍA O HUBO INGRESO INVÁLIDO.\n");
							break;
					}
					break;
				case 8: //8) Guardar datos de los empleados en archivo 'data.csv' (modo texto)
					retorno = controller_saveAsText("data2.csv",listaEmpleados);
					switch(retorno)
					{
						case 0:
							printf("\nSE GUARDARON EMPLEADOS AL ARCHIVO CON ÉXITO.\n");
							break;
						case -1:
							printf("\nERROR. LOS PARAMETROS NO SON VÁLIDOS O LA LISTA ESTÁ VACÍA.\n");
							break;
						case -2:
							printf("\nERROR AL ABRIR EL ARCHIVO\n");
							break;
					}
					break;
				case 9: //9) Guardar datos de los empleados en archivo 'data.csv' (modo binario)
					retorno = controller_saveAsBinary("data2.csv",listaEmpleados);
					switch(retorno)
					{
						case 0:
							printf("\nSE GUARDARON EMPLEADOS AL ARCHIVO CON ÉXITO.\n");
							break;
						case -1:
							printf("\nERROR. LOS PARAMETROS NO SON VÁLIDOS O LA LISTA ESTÁ VACÍA.\n");
							break;
						case -2:
							printf("\nERROR AL ABRIR EL ARCHIVO\n");
							break;
					}
					break;
				case 10: //10) Inicializar dato de los empleados
					retorno = controller_InitEmployeeDataOfList(listaEmpleados);
					switch(retorno)
					{
						case 0:
							printf("\nSE INICIALIZÓ EL DATO SELECCIONADO CON ÉXITO.\n");
							break;
						case -1:
							printf("\nERROR AL INICIALIZAR.\n");
							break;
						case -2:
							printf("\nERROR. LOS PARAMETROS NO SON VÁLIDOS O LA LISTA ESTÁ VACÍA O HUBO INGRESO INVÁLIDO.\n");
							break;
					}
					break;
				case 11: //11) Calcular sueldo de los empleados
					retorno = controller_calculateEmployeeSalary(listaEmpleados);
					switch(retorno)
					{
						case 0:
							printf("\nSE CALCULARON LOS SUELDOS CON ÉXITO.\n");
							break;
						case -1:
							printf("\nERROR AL CALCULAR SUELDO.\n");
							break;
						case -2:
							printf("\nERROR. LOS PARAMETROS NO SON VÁLIDOS O LA LISTA ESTÁ VACÍA.\n");
							break;
					}
					break;
				case 12: //12) Informar empleados con más de 100 horas de trabajo
					retorno = controller_reportingEmployeesWithMoreThan100WorkingHours(listaEmpleados);
					switch(retorno)
					{
						case -1:
							printf("\nERROR. LOS PARAMETROS NO SON VÁLIDOS O LA LISTA ESTÁ VACÍA.\n");
							break;
						case -2:
							printf("\nERROR. NO SE LOGRÓ CREAR UNA LISTA FILTRADA.\n");
							break;
						default:
							printf("\n%d EMPLEADOS TRABAJAN MÁS DE 100 HORAS.\n",retorno);
					}
					break;
				case 13: //13) Informar saldo total a pagar por sueldos
					retorno = controller_reportingTotalSalaryBalance(listaEmpleados);
					switch(retorno)
					{
						case -1:
							printf("\nERROR AL CALCULAR SALDO TOTAL.\n");
							break;
						case -2:
							printf("\nERROR. LOS PARAMETROS NO SON VÁLIDOS O LA LISTA ESTÁ VACÍA.\n");
							break;
						default:
							printf("\nSALDO TOTAL A PAGAR DE SUELDOS: %d\n",retorno);
					}
					break;
				case 14: //14) Informar empleado con mayor sueldo
					retorno = controller_informarEmpleadoConMayorSueldo(listaEmpleados);
					switch(retorno)
					{
						case -1:
							printf("\nERROR. LOS PARAMETROS NO SON VÁLIDOS O LA LISTA ESTÁ VACÍA.\n");
							break;
						case -2:
							printf("\nERROR. NO SE LOGRÓ REDUCIR LA LISTA.\n");
							break;
					}
					break;
			}
		}
		else
		{
			printf("\nSE ACABARON SUS REINTENTOS.\n");
		}
	}while(option != 15);
	return EXIT_SUCCESS;
}
