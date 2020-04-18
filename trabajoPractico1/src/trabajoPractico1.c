/*
 ============================================================================
 Name        : trabajoPractico1.c
 Author      : Ale Muñoz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 ENUNCIADO:
 Hacer una calculadora. Para ello el programa iniciará y contará con un menú de opciones:
 1. Ingresar 1er operando (A=x)
 2. Ingresar 2do operando (B=y)
 3. Calcular todas las operaciones
 	 a) Calcular la suma (A+B)
 	 b) Calcular la resta (A-B)
 	 c) Calcular la division (A/B)
 	 d) Calcular la multiplicacion (A*B)
 	 e) Calcular el factorial (A!)
 4. Informar resultados
 	 a) “El resultado de A+B es: r”
 	 b) “El resultado de A-B es: r”
 	 c) “El resultado de A/B es: r” o “No es posible dividir por cero”
 	 d) “El resultado de A*B es: r”
 	 e) “El factorial de A es: r1 y El factorial de B es: r2”
 5. Salir
 • Todas las funciones matemáticas del menú se deberán realizar en una biblioteca aparte,
 que contenga las funciones para realizar las cinco operaciones.
 • En el menú deberán aparecer los valores actuales cargados en los operandos A y B
 (donde dice “x” e “y” en el ejemplo, se debe mostrar el número cargado).
 • Deberán contemplarse los casos de error (división por cero, etc).
 • Documentar todas las funciones.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "mathFunctions.h"

#define INTMIN -2147483648
#define INTMAX 2147483647

int main(void)
{
	setbuf(stdout, NULL);
	int operandoA;
	int operandoB;
	int resultadoSuma;
	int resultadoResta;
	int resultadoProducto;
	float resultadoDivision;
	int resultadoFactorialA;
	int resultadoFactorialB;
	int opcion;
	int respuesta;

	do
	{
		respuesta = utn_getNumeroInt(&opcion, "Elija una opción:\n\n1. Ingresar 1er operando (A=x) \n2. Ingresar 2do operando (B=y) \n3. Calcular la suma (A+B) \n4. Calcular la resta (A-B) \n5. Calcular la multiplicacion (A*B) \n6. Calcular la division (A/B) \n7. Calcular el factorial (A!) \n8. Salir \n", "NO ES UNA OPCIÓN VALIDA\n", 1, 8, 2);
		if(respuesta == 0)
		{
			switch(opcion)
			{
				case 1:
					respuesta = utn_getNumeroInt(&operandoA, "Ingrese el 1er operando: \n", "NO ES UNA OPCIÓN VALIDA\n", INTMIN, INTMAX, 2);
					printf("A = %d\n", operandoA);
					break;
				case 2:
					utn_getNumeroInt(&operandoB, "Ingrese el 2do operando: \n", "NO ES UNA OPCIÓN VALIDA\n", INTMIN, INTMAX, 2);
					printf("B = %d\n", operandoB);
					break;
				case 3:
					respuesta = utn_Sumar(&resultadoSuma, operandoA, operandoB);
					if(respuesta == 0)
					{
						printf("El resultado de %d+%d es: %d\n", operandoA, operandoB, resultadoSuma);
					}
					else
					{
						printf("ERROR.\n");
					}
					break;
				case 4:
					respuesta = utn_Restar(&resultadoResta, operandoA, operandoB);
					if(respuesta == 0)
					{
						printf("El resultado de %d-%d es: %d\n", operandoA, operandoB, resultadoResta);
					}
					else
					{
						printf("ERROR.\n");
					}
					break;
				case 5:
					respuesta = utn_Multiply(&resultadoProducto, operandoA, operandoB);
					if(respuesta == 0)
					{
						printf("El resultado de %d*%d es: %d\n", operandoA, operandoB, resultadoProducto);
					}
					else
					{
						printf("ERROR.\n");
					}
					break;
				case 6:
					respuesta = utn_Dividir(&resultadoDivision, operandoA, operandoB);
					if(respuesta == 0)
					{
						printf("El resultado de %d/%d es: %f\n", operandoA, operandoB, resultadoDivision);
					}
					else
					{
						printf("El resultado de %d/%d es: INDEFINIDO\n", operandoA, operandoB);
					}
					break;
				case 7:
					respuesta = utn_CalcularFactorial(&resultadoFactorialA, operandoA);
					if(respuesta != -1)
					{
						printf("El factorial de %d es: %d\n", operandoA, resultadoFactorialA);
					}
					else
					{
						printf("El factorial de %d es: INDEFINIDO\n", operandoA);
					}
					respuesta = utn_CalcularFactorial(&resultadoFactorialB, operandoB);
					if(respuesta != -1)
					{
						printf("El factorial de %d es: %d\n", operandoB, resultadoFactorialB);
					}
					else
					{
						printf("El factorial de %d es: INDEFINIDO\n", operandoB);
					}
					break;
			}
		}
		else
		{
			printf("ERROR.\n");
		}
	}while(opcion!=8);

	return EXIT_SUCCESS;
}
