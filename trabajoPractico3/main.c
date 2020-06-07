#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "utn.h"

/****************************************************

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

*****************************************************/


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
									"10) Salir\n","\nOPCION INVALIDA.",1,10,2) )
		{
			switch(option)
			{
				case 1: //1) Cargar datos de los empleados desde archivo 'data.csv' (modo texto)
					retorno = controller_loadFromText("data.csv",listaEmpleados);
					switch(retorno)
					{
						case -1:
							printf("\nERROR. LOS PARAMETROS NO SON VALIDOS\n");
							break;
						case -2:
							printf("\nERROR AL ABRIR EL ARCHIVO.\n");
							break;
						case -3:
							printf("\nERROR. NO SE PUDO CREAR EMPLEADO EN MEMORIA.\n");
							break;
						case -4:
							printf("\nERROR. EL PUNTERO A LA LISTA ES NULL.\n");
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
							printf("\nERROR. LOS PARAMETROS NO SON VALIDOS\n");
							break;
						case -2:
							printf("\nERROR AL ABRIR EL ARCHIVO.\n");
							break;
						case -3:
							printf("\nERROR. NO SE PUDO CREAR EMPLEADO EN MEMORIA.\n");
							break;
						case -4:
							printf("\nERROR. EL PUNTERO A LA LISTA ES NULL.\n");
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
							printf("\nERROR. LOS PARAMETROS NO SON VÁLIDOS\n");
							break;
						case -2:
							printf("\nERROR. SE INGRESÓ AL MENOS UN DATO INVALIDO\n");
							break;
						case -3:
							printf("\nERROR. NO SE PUDO AGREGAR EMPLEADO\n");
							break;
						case -4:
							printf("\nERROR. EL PUNTERO A LA LISTA ES NULL\n");
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
							printf("\nERROR. LOS PARAMETROS NO SON VÁLIDOS.\n");
							break;
						case -2:
							printf("\nSE ACABARON SUS REINTENTOS. ID INVALIDO.\n");
							break;
						case -3:
							printf("\nERROR. EL PUNTERO A LA LISTA ES NULL O EL INDICE ES ERRONEO.\n");
							break;
						case -4:
							printf("\nERROR. NO SE OBTUVO ID.\n");
							break;
						case -5:
							printf("\nERROR. SE INGRESO AL MENOS UN DATO INVALIDO.\n");
							break;
						case -6:
							printf("\nERROR. NO SE LOGRÓ ASIGNAR AL MENOS UN DATO A UN CAMPO DEL EMPLEADO.\n");
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
						printf("\nERROR. LOS PARAMETROS NO SON VÁLIDOS.\n");
						break;
					case -2:
						printf("\nSE ACABARON SUS REINTENTOS. ID INVALIDO.\n");
						break;
					case -3:
						printf("\nERROR. EL PUNTERO A LA LISTA ES NULL O EL INDICE ES ERRONEO.\n");
						break;
					case -4:
						printf("\nERROR. NO SE OBTUVO ID.\n");
						break;
					case -5:
						printf("\nERROR. EL PUNTERO A LA LISTA ES NULL O EL INDICE ES ERRONEO.\n");
						break;
					}
					break;
				case 6: //6) Listar empleados
					if(controller_ListEmployee(listaEmpleados) == -1)
					{
						printf("\nERROR.\n");
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
							printf("\nERROR.\n");
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
						printf("\nERROR. LOS PARAMETROS NO SON VALIDOS\n");
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
						printf("\nERROR. LOS PARAMETROS NO SON VALIDOS\n");
						break;
					case -2:
						printf("\nERROR AL ABRIR EL ARCHIVO\n");
						break;
					}
					break;
			}
		}
		else
		{
			printf("\nSE ACABARON SUS REINTENTOS.\n");
		}
	}while(option != 10);
	return 0;
}
