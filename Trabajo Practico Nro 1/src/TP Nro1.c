/*
 ============================================================================
 Name        : Nicolas Caretti
 Division    : 1A
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "OperacionesYMenu.h"

int main(void)
{
	setbuf(stdout, NULL);
	int primerOperando;
	int segundoOperando;
	int flagPrimerOperando = 0;
	int flagSegundoOperando = 0;
	int flagCambioOperando = 0;
	int flagTercerOpcion = 0;
	int flagSalida = 0;
	int resSuma;
	int resResta;
	float resDivision;
	int resMultiplicacion;
	int resFactorialUno;
	int resFactorialDos;
	int retornoFac;
	int retornoDiv;

	do
	{
		switch(menu(&primerOperando, &segundoOperando, &flagPrimerOperando, &flagSegundoOperando))
		{
			case 1:
				obtenerPrimerOperando(&primerOperando);
				flagPrimerOperando = 1;
				flagCambioOperando = flagCambioOperando + 1;
			break;

			case 2:
				obtenerSegundoOperando(&segundoOperando);
				flagSegundoOperando = 1;
				flagCambioOperando = flagCambioOperando + 1;
			break;

			case 3:
				if(flagPrimerOperando == 1 && flagSegundoOperando == 1)
				{
					system("cls");
					//SUMA
					if(calcularSuma(&primerOperando, &segundoOperando,  &resSuma))
					{
						printf("A- Calcular la suma (%d + %d)\n", primerOperando, segundoOperando);
					}
					else
					{
						printf("Error, no se pudo calcular la suma.\n");
					}

					//RESTA
					if(calcularResta(&primerOperando, &segundoOperando, &resResta))
					{
						printf("B- Calcular la resta (%d - %d)\n", primerOperando, segundoOperando);
					}
					else
					{
						printf("Error, no se pudo calcular la resta.\n");
					}

					//DIVISION
					retornoDiv = calcularDivision(&primerOperando, &segundoOperando, &resDivision);
					if(retornoDiv != 0)
					{
						printf("C- Calcular la division (%d / %d)\n", primerOperando, segundoOperando);

					}
					else
					{
						printf("Error, no se pudo calcular la division.\n");
					}

					//MULTIPLICACION
					if(calcularMultiplicacion(&primerOperando, &segundoOperando, &resMultiplicacion))
					{
						printf("D- Calcular la multiplicacion (%d * %d)\n", primerOperando, segundoOperando);
					}
					else
					{
						printf("Error, no se pudo calcular la multiplicacion.\n");
					}

					//FACTORIAL
					retornoFac = calcularFactorial(&primerOperando, &segundoOperando, &resFactorialUno, &resFactorialDos);
					if(retornoFac != 0)
					{
						printf("E- Calcular el factorial (%d! y %d!)\n", primerOperando, segundoOperando);
					}
					else
					{
						printf("Error, no se pudo calcular el factorial.\n");
					}

					flagCambioOperando = 1;
					flagTercerOpcion = 1;
					system("pause");
				}
				else
				{
					printf("Error, primero debe ingresar los dos operandos.\n");
					system("pause");
				}
			break;

			case 4:
				if(flagTercerOpcion == 1)
				{
					if(flagCambioOperando == 1)
					{
						system("cls");
						printf("A- El resultado de %d + %d es: %d\n", primerOperando, segundoOperando, resSuma);
						printf("B- El resultado de %d - %d es: %d\n", primerOperando, segundoOperando, resResta);

						if(retornoDiv == -1)
						{
							printf("C- No se puede dividir por cero.\n");
						}
						else
						{
							printf("C- El resultado de %d / %d es: %.2f\n", primerOperando, segundoOperando, resDivision);
						}

						printf("D- El resultado de %d * %d es: %d\n", primerOperando, segundoOperando, resMultiplicacion);

						if(retornoFac == 3)
						{
							printf("F- El factorial de %d es: %d | El factorial de %d es: %d\n", primerOperando, resFactorialUno, segundoOperando, resFactorialDos);
						}
						else if(retornoFac == 2)
						{
							printf("F- No se puede calcular el factorial de un negativo | El factorial de %d es: %d\n", segundoOperando, resFactorialDos);
						}
						else if(retornoFac == 1)
						{
							printf("F- El factorial de %d es: %d | No se puede calcular el factorial de un negativo\n", primerOperando, resFactorialUno);
						}
						else if(retornoFac == -1)
						{
							printf("F- No se puede calcular el factorial ya que ambos son numeros negativos.\n");
						}

						system("pause");
					}
					else
					{
						printf("Error, cambio alguno de los operandos, calcule nuevamente antes de imprimir resultados.\n");
						flagCambioOperando = 0;
						system("pause");
					}
				}
				else
				{
					printf("Error, primero debe ingresar los dos operandos y debe calcular las operaciones.\n");
					system("pause");
				}
			break;

			case 5:
				printf("Ha salido con exito, gracias por usar la aplicacion.\n");
				flagSalida = 1;
			break;

			default:
				printf("Error, ingrese una opcion valida.\n");
				system("pause");
			break;
		}

	}while(flagSalida != 1);


	return EXIT_SUCCESS;
}

