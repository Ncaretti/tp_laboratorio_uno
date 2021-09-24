#include <stdio.h>
#include <stdlib.h>
#include "OperacionesYMenu.h"

/**
 * @fn int menu(int*, int*, int*, int*)
 * @brief Imprime las opciones del menu y toma la opcion elegida por el usuario
 *
 * @param primerOperando primer operando ingresado previamente por el usuario, se utiliza para mostrarlo en lugar de la 'x'
 * @param segundoOperando segundo operando ingresado previamente por el usuario, se utiliza para mostrarlo en lugar de la 'y'
 * @param flagPrimerOperando bandera utilizada para indicar si el usuario ingreso o no el valor del primer operando
 * @param flagSegundoOperando bandera utilizada para indicar si el usuario ingreso o no el valor del segundo operando
 * @return
 */
int menu(int* primerOperando, int* segundoOperando, int* flagPrimerOperando, int* flagSegundoOperando)
{
	system("cls");
	int opcion;

	printf("-----------INGRESE UNA OPCION-----------\n");

	if(*flagPrimerOperando == 0)
	{
		printf("1- Ingresar 1er operando (A = x)\n");
	}
	else
	{
		printf("1- Cambiar el 1er operando (A = %d)\n", *primerOperando);
	}

	if(*flagSegundoOperando == 0)
	{
		printf("2- Ingresar 2do operando (B = y)\n");
	}
	else
	{
		printf("2- Cambiar el 2do operando (B = %d)\n", *segundoOperando);
	}

	printf("3- Calcular todas las operaciones\n");
	printf("4- Informar resultados\n");
	printf("5- Salir\n");
	scanf("%d", &opcion);

	return opcion;

}

/**
 * @fn void obtenerPrimerOperando(int*)
 * @brief obtiene el primer operando y valida que no se haya ingresado un caracter no numerico
 *
 * @param primerOperando puntero donde se almacena el primer operando luego de ser validado
 */
void obtenerPrimerOperando(int* primerOperando)
{
	int verificacion;

	printf("Ingrese el primer operando: ");
	fflush(stdin);
	if(scanf("%d", primerOperando))
	{
		verificacion = 1;
	}
	else
	{
		do
		{
			printf("Error, ingrese un caracter numerico: ");
			fflush(stdin);
			if(scanf("%d", primerOperando))
			{
				verificacion = 1;
			}
			else
			{
				verificacion = 0;
			}

		}while(verificacion == 0);
	}

}

/**
 * @fn void obtenerSegundoOperando(int*)
 * @brief obtiene el segundo operando y valida que no se haya ingresado un caracter no numerico
 *
 * @param segundoOperando puntero donde se almacena el segundo operando luego de ser validado
 */
void obtenerSegundoOperando(int* segundoOperando)
{
	int verificacion;

	printf("Ingrese el segundo operando: ");
	fflush(stdin);
	if(scanf("%d", segundoOperando))
	{
		verificacion = 1;
	}
	else
	{
		do
		{
			printf("Error, ingrese un caracter numerico: ");
			fflush(stdin);
			if(scanf("%d", segundoOperando))
			{
				verificacion = 1;
			}
			else
			{
				verificacion = 0;
			}

		}while(verificacion == 0);
	}

}

/**
 * @fn int calcularSuma(int*, int*, int*)
 * @brief calcula la suma de los operandos
 *
 * @param primerOperando puntero que almacena el primer operando
 * @param segundoOperando puntero que almacena el segundo operando
 * @param resSuma puntero que almacena la suma entre el primer y segundo operando
 * @return retorna 1 si salio bien o 0 si algo salio mal
 */
int calcularSuma(int* primerOperando, int* segundoOperando, int* resSuma)
{
	int ret = 0;

	if(primerOperando != NULL && segundoOperando != NULL)
	{
		*resSuma = *primerOperando + *segundoOperando;
		ret = 1;
	}

	return ret;
}

/**
 * @fn int calcularResta(int*, int*, int*)
 * @brief calcula la resta de los operandos
 *
 * @param primerOperando puntero que almacena el primer operando
 * @param segundoOperando puntero que almacena el segundo operando
 * @param resResta puntero que almacena la resta entre el primer y segundo operando
 * @return retorna 1 si salio bien o 0 si algo salio mal
 */
int calcularResta(int* primerOperando, int* segundoOperando, int* resResta)
{
	int ret = 0;

	if(primerOperando != NULL && segundoOperando != NULL)
	{
		*resResta = *primerOperando - *segundoOperando;
		ret = 1;
	}

	return ret;
}

/**
 * @fn int calcularDivision(int*, int*, float*)
 * @brief calcula la division de los operandos
 *
 * @param primerOperando puntero que almacena el primer operando
 * @param segundoOperando puntero que almacena el segundo operando
 * @param resDivision puntero que almacena la division entre el primer y segundo operando
 * @return  retorna 1 si salio bien, 0 si algo salio mal y -1 si se realizo una division por 0
 */
int calcularDivision(int* primerOperando, int* segundoOperando, float* resDivision)
{
	int ret = 0;

	if(primerOperando != NULL && segundoOperando != NULL)
	{
		if(*segundoOperando != 0)
		{
			*resDivision = (float)*primerOperando / *segundoOperando;
			ret = 1;
		}
		else
		{
			ret = -1;
		}
	}

	return ret;
}

/**
 * @fn int calcularMultiplicacion(int*, int*, int*)
 * @brief calcula la multiplicacion de los operandos
 *
 * @param primerOperando puntero que almacena el primer operando
 * @param segundoOperando puntero que almacena el segundo operando
 * @param resDivision puntero que almacena la division entre el primer y segundo operando
 * @return retorna 1 si salio bien o 0 si algo salio mal
 */
int calcularMultiplicacion(int* primerOperando, int* segundoOperando, int* resMultiplicacion)
{
	int ret = 0;

	if(primerOperando != NULL && segundoOperando != NULL)
	{
		*resMultiplicacion = *primerOperando * *segundoOperando;
		ret = 1;
	}

	return ret;
}

/**
 * @fn int calcularFactorial(int*, int*, int*, int*)
 * @brief calcula el factorial de ambos operandos por sepado
 *
 * @param primerOperando puntero que almacena el primer operando
 * @param segundoOperando puntero que almacena el segundo operando
 * @param resFactorialUno puntero que almacena el resultado del factorial del primer operando
 * @param resFactorialDos puntero que almacena el resultado del factorial del segundo operando
 * @return retorna 3 si ambos factoriales se pudieron calcular, 2 si solo pudo calcularse el segundo factorial, 1 si solo pudo calcularse el primer
 * factorial, -1 si no pudo calcularse ninguno de los dos factoriales y 0 si hubo un error al calcular los factoriales
 */
int calcularFactorial(int* primerOperando, int* segundoOperando, int* resFactorialUno, int* resFactorialDos)
{
	int ret = 0;
	int flagPrimerFactorial = 0;
	int flagSegundoFactorial = 0;
	int i;
	int j;
	*resFactorialUno = 1;
	*resFactorialDos = 1;

	if(primerOperando != NULL && segundoOperando != NULL)
	{
		if(*primerOperando >= -1)
		{
			if(*primerOperando != 0)
			{
				for(i=1;i<=*primerOperando;i++)
				{
					*resFactorialUno *= i;
					flagPrimerFactorial = 1;
				}
			}
			else
			{
				*resFactorialUno = 1;
				flagPrimerFactorial = 1;
			}
		}


		if(*segundoOperando >= -1)
		{
			if(*segundoOperando != 0)
			{
				for(j=1;j<=*segundoOperando;j++)
				{
					*resFactorialDos *= j;
					flagSegundoFactorial = 1;
				}
			}
			else
			{
				*resFactorialDos = 1;
				flagSegundoFactorial = 1;
			}
		}
	}

	if(flagPrimerFactorial == 1 && flagSegundoFactorial == 1)
	{
		ret = 3;
	}
	else if(flagPrimerFactorial == 0 && flagSegundoFactorial == 1)
	{
		ret = 2;
	}
	else if(flagPrimerFactorial == 1 && flagSegundoFactorial == 0)
	{
		ret = 1;
	}
	else if(flagPrimerFactorial == 0 && flagSegundoFactorial == 0)
	{
		ret = -1;
	}

	return ret;
}
