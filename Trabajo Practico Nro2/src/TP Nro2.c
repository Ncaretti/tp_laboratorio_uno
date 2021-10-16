/*
 ============================================================================
 Name        : TP.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayEmployees.h"

#define TAM 1000
#define OCUPADO 1
#define VACIO 0


int main(void)
{
	setbuf(stdout, NULL);
	system("cls");
	int opcion;
	char nombre[51];
	char apellido[51];
	float salario;
	int sector;
	int id = 1;
	int flagAlta = 0;
	int i;
	int opcionCaseCuatro;
	int validacionCaseCuatro = 0;
	int opcionCuatro;
	int validacionMenuCuatro = 0;

	eEmpleado listaEmpleados[TAM];/*= {
			{1,"Jose","Gutierrez",20000,2,OCUPADO},
			{2,"Nahiara","Velo",65000,1,OCUPADO},
			{3,"Hugo","Morales",70000,3,OCUPADO},
			{4,"Hector","Moyano",160000,3,OCUPADO},
			{5,"Hugo","Rosales",50000,1,OCUPADO}
			};*/


	if(!iniciarEmpleados(listaEmpleados, TAM))
	{
		printf("Hubo un error al vaciar la lista.\n");
	}

	do
	{
		printf("\n-----------INGRESE UNA OPCION-----------\n"
			   "1- ALTAS\n"
			   "2- MODIFICAR\n"
			   "3- BAJA\n"
			   "4- INFORMAR\n"
			   "5- SALIR\n");
		scanf("%d", &opcion);



		switch(opcion)
		{
			case 1:
				if(agregarEmpleado(listaEmpleados, TAM, &id, nombre, apellido, &salario, &sector))
				{
					printf("Empleado dado de alta con exito.\n");
					flagAlta = 1;
					system("pause");
				}
				else
				{
					printf("Hubo un error al dar de alta el empleado.\n");
					system("pause");
				}

			break;

			case 2:
				if(flagAlta)
				{
					if(modificarEmpleado(listaEmpleados, TAM))
					{
						printf("Empleado modificado con exito.\n");
						system("pause");
					}
					else
					{
						printf("Hubo un error al modificar el empleado.\n");
						system("pause");
					}
				}
				else
				{
					printf("Error, no hay empleados ingresados en el sistema.\n");
					system("pause");
				}

			break;

			case 3:
				if(flagAlta)
				{
					if(removerEmpleado(listaEmpleados, TAM))
					{
						printf("Empleado dado de baja con exito.\n");
						flagAlta = 0;

						for(i=0;i<TAM;i++)
						{
							if(listaEmpleados[i].isEmpty == OCUPADO)
							{
								flagAlta = 1;
								break;
							}
						}
						system("pause");
					}
					else
					{
						printf("Hubo un error al dar de baja el empleado.\n");
						system("pause");
					}
				}
				else
				{
					printf("Error, no hay empleados ingresados en el sistema.\n");
					system("pause");
				}

			break;

			case 4:
				if(flagAlta)
				{
					printf("\n-----------INGRESE UNA OPCION-----------\n"
						   "1- ORDENAR Y LISTAR EMPLEADOS ALFABETICAMENTE POR APELLIDO Y SECTOR\n"
						   "2- TOTAL, PROMEDIO DE LOS SALARIOS Y CUANTOS EMPLEADOS SUPERAN EL SALARIO PROMEDIO\n");
					if(scanf("%d", &opcionCuatro))
					{
						validacionMenuCuatro = 1;
					}
					else
					{
						do
						{
							printf("Error, ingrese un salario valido: ");
							fflush(stdin);
							if(scanf("%d", &opcionCuatro))
							{
								validacionMenuCuatro = 1;
							}
							else
							{
								validacionMenuCuatro = 0;
							}

						}while(validacionMenuCuatro == 0);
					}

					if(opcionCuatro == 1)
					{
						printf("Ingrese orden ascendente(1) o orden descendente(0): ");
						fflush(stdin);
						if((scanf("%d", &opcionCaseCuatro)))
						{
							if(opcionCaseCuatro >= 0 && opcionCaseCuatro <= 1)
							{
								validacionCaseCuatro = 1;
							}
							else
							{
								do
								{
									printf("b\n");
									printf("Error, ingrese un orden correcto: ");
									fflush(stdin);
									if(scanf("%d", &opcionCaseCuatro))
									{
										if(opcionCaseCuatro >= 0 && opcionCaseCuatro <= 1)
										{
											validacionCaseCuatro = 1;
										}
									}
									else
									{
										validacionCaseCuatro = 0;
									}
								}while(validacionCaseCuatro == 0);
							}
						}
						else
						{
							do
							{
								printf("a\n");
								printf("Error, ingrese un sector valido: ");
								fflush(stdin);
								if(scanf("%d", &opcionCaseCuatro))
								{
									if(opcionCaseCuatro >= 1 && opcionCaseCuatro <= 3)
									{
										validacionCaseCuatro = 1;
									}
								}
								else
								{
									validacionCaseCuatro = 0;
								}

							}while(validacionCaseCuatro == 0);
						}

						if(validacionCaseCuatro == 1)
						{
							clasificarEmpleadosPorNombre(listaEmpleados, TAM, opcionCaseCuatro);
							system("pause");
						}
					}
					else
					{
						totalYPromedioSalarios(listaEmpleados, TAM);
					}
				}
				else
				{
					printf("Error, no hay empleados ingresados en el sistema.\n");
					system("pause");
				}
			break;

			case 5:
				printf("Ha salido con exito.\n");
			break;

			default:
				printf("Error, elija una opcion valida.\n");
				system("pause");
			break;
		}
	}while(opcion != 5);


	return EXIT_SUCCESS;
}

