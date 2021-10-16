#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayEmployees.h"

#define TAM 1000
#define OCUPADO 1
#define VACIO 0

/** \brief To indicate that all position in the array are empty,
 * this function put the flag (isEmpty) in TRUE in all
 * position of the array
 * \param list Employee* Pointer to array of employees
 * \param len int Array length
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */
int iniciarEmpleados(eEmpleado* listaEmpleados, int tam)
{
	int ret = 0;
	int i;

	if(listaEmpleados != NULL && tam > 0)
	{
		for(i=0;i<tam;i++)
		{
			listaEmpleados[i].isEmpty = VACIO;
			ret = 1;
		}
	}

	return ret;
}

/**
 * @fn int buscarLibre(eEmpleado*, int)
 * @brief busca una posicion libre del array
 *
 * @param listaEmpleados puntero del array de empleados
 * @param tam tamanio del array
 * @return retorna -1 si hubo un error o retorna la posicion libre
 */
int buscarLibre(eEmpleado* listaEmpleados, int tam)
{
	int indice = -1;
	int i;

	if(listaEmpleados != NULL && tam > 0)
	{
		for(i=1;i<tam;i++)
		{
			if(listaEmpleados[i].isEmpty == VACIO)
			{
				indice = i;
				break;
			}
		}
	}
	return indice;
}

/** \brief add in a existing list of employees the values received as parameters
 * in the first empty position
 * \param list employee*
 * \param len int
 * \param id int
 * \param name[] char
 * \param lastName[] char
 * \param salary float
 * \param sector int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 */
int agregarEmpleado(eEmpleado* listaEmpleados, int tam, int* id, char nombre[], char apellido[], float* salario, int* sector)
{
	int ret = 0;
	int indice;
	int i;
	int tamChar;
	int validacionNombre = 0;
	int validacionApellido = 0;
	int validacionSalario = 0;
	int validacionSector = 0;
	eEmpleado miEmpleado;


	if(listaEmpleados != NULL && tam > 0 && id != NULL)
	{
		indice = buscarLibre(listaEmpleados, tam);

		if(indice != -1)
		{

			//ID//
			miEmpleado.id = *id;
			(*id)++;

			//NOMBRE//
			do
			{
				printf("Ingrese nombre: ");
				scanf("%s", nombre);
				tamChar = strlen(nombre);

				for(i=0;i<tamChar;i++)
				{
					if(!((nombre[i] >= 65 && nombre[i] <= 90) || (nombre[i] >= 97 && nombre[i] <= 122)))
					{
						printf("Error, ingrese un nombre valido\n");
						validacionNombre = 0;
						break;
					}

					validacionNombre = 1;
				}
			}while(validacionNombre == 0);

			if(validacionNombre == 1)
			{
				strcpy(miEmpleado.nombre, nombre);
			}


			//APELLIDO//
			do
			{
				printf("Ingrese apellido: ");
				scanf("%s", apellido);
				tamChar = strlen(apellido);

				for(i=0;i<tamChar;i++)
				{
					if(!((apellido[i] >= 65 && apellido[i] <= 90) || (apellido[i] >= 97 && apellido[i] <= 122)))
					{
						printf("Error, ingrese un apellido valido\n");
						validacionApellido = 0;
						break;
					}

					validacionApellido = 1;
				}
			}while(validacionApellido == 0);

			if(validacionApellido == 1)
			{
				strcpy(miEmpleado.apellido, apellido);
			}


			//SALARIO//
			printf("Ingrese salario: ");
			fflush(stdin);
			if(scanf("%f", salario))
			{
				validacionSalario = 1;
			}
			else
			{
				do
				{
					printf("Error, ingrese un salario valido: ");
					fflush(stdin);
					if(scanf("%f", salario))
					{
						validacionSalario = 1;
					}
					else
					{
						validacionSalario = 0;
					}

				}while(validacionSalario == 0);
			}

			if(validacionSalario == 1)
			{
				miEmpleado.salario = *salario;
			}


			//SECTOR//
			printf("Ingrese el sector (1-3): ");
			fflush(stdin);
			if((scanf("%d", sector)))
			{
				if(*sector >= 1 && *sector <= 3)
				{
					validacionSector = 1;
				}
				else
				{
					do
					{
						printf("b\n");
						printf("Error, ingrese un sector valido: ");
						fflush(stdin);
						if(scanf("%d", sector))
						{
							if(*sector >= 1 && *sector <= 3)
							{
								validacionSector = 1;
							}
						}
						else
						{
							validacionSector = 0;
						}
					}while(validacionSector == 0);
				}
			}
			else
			{
				do
				{
					printf("a\n");
					printf("Error, ingrese un sector valido: ");
					fflush(stdin);
					if(scanf("%d", sector))
					{
						if(*sector >= 1 && *sector <= 3)
						{
							validacionSector = 1;
						}
					}
					else
					{
						validacionSector = 0;
					}

				}while(validacionSector == 0);
			}

			if(validacionSector == 1)
			{
				miEmpleado.sector = *sector;
			}

			miEmpleado.isEmpty = OCUPADO;
			listaEmpleados[indice] = miEmpleado;

			ret = 1;
		}
		else
		{
			printf("No hay lugar en el sistema.\n");
		}
	}

	return ret;
}

/** \brief print the content of one employe
 *
 * \param list Employee*
 *
 */
void mostrarEmpleado(eEmpleado miEmpleado)
{
	printf("%d\t %10s\t %10s\t $%.2f\t %d\n", miEmpleado.id, miEmpleado.nombre, miEmpleado.apellido, miEmpleado.salario, miEmpleado.sector);
}

/** \brief print the content of employees array
 *
 * \param list Employee*
 * \param length int
 * \return int
 *
 */
int mostrarEmpleados(eEmpleado* listaEmpleados, int tam)
{
	int ret = -1;
	int i;

	printf("ID\t    NOMBRE\t   APELLIDO\t SALARIO\t SECTOR\n");
	if(listaEmpleados != NULL && tam > 0)
	{
		for(i=0;i<tam;i++)
		{
			if(listaEmpleados[i].isEmpty == OCUPADO)
			{
				mostrarEmpleado(listaEmpleados[i]);
			}

			ret = 1;
		}
	}

	return ret;
}

/** \brief find an Employee by Id en returns the index position in array.
 *
 * \param list Employee*
 * \param len int
 * \param id int
 * \return Return employee index position or (-1) if [Invalid length or NULL
pointer received or employee not found]
 *
 */

int buscarEmpleadoPorId(eEmpleado* listaEmpleados, int tam, int id)
{
	int index = -1;
	int i;

	for(i=0; i<tam; i++)
	{
		if(listaEmpleados[i].isEmpty == OCUPADO)
		{
			if(listaEmpleados[i].id == id)
			{
				index = id;
				break;
			}
		}
		else
		{
			index = -1;
		}
	}

	return index;
}

/**
 * @fn int modificarEmpleado(eEmpleado*, int)
 * @brief modifica en empleado que desee ingresando el id
 *
 * @param listaEmpleados puntero que contiene la lista de empleados
 * @param tam tamanio del array de empleados
 * @return
 */
int modificarEmpleado(eEmpleado* listaEmpleados, int tam)
{
	int idIngresado;
	int indice;
	int ret = -1;
	int opcion;
	int tamChar;
	int i;
	char nombre[51];
	int validacionNombre = 0;
	char apellido[51];
	int validacionApellido = 0;
	float salario;
	int validacionSalario = 0;
	int sector;
	int validacionSector = 0;

	printf("\n************************LISTA EMPLEADOS************************\n");
	mostrarEmpleados(listaEmpleados, tam);
	printf("***************************************************************\n");

	printf("Ingrese el ID del empleado a modificar: ");
	scanf("%d", &idIngresado);

	indice = buscarEmpleadoPorId(listaEmpleados, tam, idIngresado);
	if(indice == idIngresado)
	{
		do
		{
		 printf("1.Modificar nombre del empleado\n");
		 printf("2.Modificar apellido del empleado\n");
		 printf("3.Modificar salario del empleado\n");
		 printf("4.Modificar sector del empleado\n");
		 printf("5.Salir\n");
		 printf("\n¿Que quiere modificar?: ");
		 scanf("%d", &opcion);

		switch(opcion)
		{
			case 1:
				do
				{
					printf("Ingrese nombre nuevo: ");
					scanf("%s", nombre);
					tamChar = strlen(nombre);

					for(i=0;i<tamChar;i++)
					{
						if(!((nombre[i] >= 65 && nombre[i] <= 90) || (nombre[i] >= 97 && nombre[i] <= 122)))
						{
							printf("Error, ingrese un nombre valido\n");
							validacionNombre = 0;
							break;
						}

						validacionNombre = 1;
						ret = 1;
					}
				}while(validacionNombre == 0);

				if(validacionNombre == 1)
				{
					strcpy(listaEmpleados[indice].nombre, nombre);
				}
			break;

			case 2:
				do
				{
					printf("Ingrese apellido nuevo: ");
					scanf("%s", apellido);
					tamChar = strlen(apellido);

					for(i=0;i<tamChar;i++)
					{
						if(!((apellido[i] >= 65 && apellido[i] <= 90) || (apellido[i] >= 97 && apellido[i] <= 122)))
						{
							printf("Error, ingrese un apellido valido\n");
							validacionApellido = 0;
							break;
						}

						validacionApellido = 1;
						ret = 2;
					}
				}while(validacionApellido == 0);

				if(validacionApellido == 1)
				{
					strcpy(listaEmpleados[indice].apellido, apellido);
				}
			break;

			case 3:
				printf("Ingrese salario nuevo: ");
				fflush(stdin);
				if(scanf("%f", &salario))
				{
					validacionSalario = 1;
					ret = 3;
				}
				else
				{
					do
					{
						printf("Error, ingrese un salario valido: ");
						fflush(stdin);
						if(scanf("%f", &salario))
						{
							validacionSalario = 1;
							ret = 3;
						}
						else
						{
							validacionSalario = 0;
						}

					}while(validacionSalario == 0);
				}

				if(validacionSalario == 1)
				{
					listaEmpleados[indice].salario = salario;
				}
			break;

			case 4:
				printf("Ingrese el nuevo sector (1-3): ");
				fflush(stdin);
				if(scanf("%d", &sector))
				{
					if(sector >= 1 && sector <= 3)
					{
						validacionSector = 1;
					}
					else
					{
						do
						{
							printf("Error, ingrese un sector valido: ");
							fflush(stdin);
							if(scanf("%d", &sector))
							{
								if(sector >= 1 && sector <= 3)
								{
									validacionSector = 1;
								}
							}
							else
							{
								validacionSector = 0;
							}
						}while(validacionSector == 0);
					}
				}
				else
				{
					do
					{
						printf("Error, ingrese un sector valido: ");
						fflush(stdin);
						if(scanf("%d", &sector))
						{
							if(sector >= 1 && sector <= 3)
							{
								validacionSector = 1;
							}
						}
						else
						{
							validacionSector = 0;
						}

					}while(validacionSector == 0);
				}

				if(validacionSector == 1)
				{
					listaEmpleados[indice].sector = sector;
				}
			break;

			case 5:
				printf("Ha salido con exito de las modificaciones.\n");

			break;
			}
		}while(opcion != 5);
	}
	else
	{
		printf("Error, no hay ningun empleado con la id ingresada.\n");
	}

	return ret;
}

/** \brief Remove a Employee by Id (put isEmpty Flag in 1)
 *
 * \param list Employee*
 * \param len int
 * \param id int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a employee] - (0) if Ok
 *
 */

int removerEmpleado(eEmpleado* listaEmpleados, int tam)
{
	int ret = 0;
	int idIngresado;
	int validacionID = 0;
	int indice;

	if(listaEmpleados != NULL && tam > 0)
	{

		mostrarEmpleados(listaEmpleados, tam);

		printf("\nIngrese el ID del empleado a dar de baja: ");
		fflush(stdin);
		if(scanf("%d", &idIngresado))
		{
			validacionID = 1;
		}
		else
		{
			do
			{
				printf("Error, ingrese un ID valido: ");
				fflush(stdin);
				if(scanf("%d", &idIngresado))
				{
					validacionID = 1;
				}
				else
				{
					validacionID = 0;
				}

			}while(validacionID == 0);
		}

		indice = buscarEmpleadoPorId(listaEmpleados, tam, idIngresado);

		if(indice != -1)
		{
			listaEmpleados[indice].isEmpty = VACIO;
			ret = 1;
		}
		else
		{
			printf("Error, no hay ningun empleado con el ID ingresado.\n");
		}
	}
	return ret;
}

/**
 * @fn int clasificarEmpleadosPorNombre(eEmpleado*, int, int)
 * @brief funcion que ordena a los empleados por orden alfabetico ascendente(1) o descendente(0)
 *
 * @param listaEmpleados puntero que contiene la lista de empleados
 * @param tam tamanio del array
 * @param orden parametro ingresado por el usuario: 1-ascendente 0-descendente
 * @return
 */
int clasificarEmpleadosPorNombre(eEmpleado* listaEmpleados, int tam, int orden)
{
	int ret = -1;
	int i;
	int j;
	eEmpleado auxEmpleado;

	if(listaEmpleados != NULL && tam > 0)
	{
		for(i=0;i<tam;i++)
		{
			if(orden == 1)
			{
				for(j=i+1;j<tam;j++)
				{
					if(strcmp(listaEmpleados[i].nombre, listaEmpleados[j].nombre) > 0)
					{
						auxEmpleado = listaEmpleados[i];
						listaEmpleados[i] = listaEmpleados[j];
						listaEmpleados[j] = auxEmpleado;
					}
					else if(strcmp(listaEmpleados[i].nombre, listaEmpleados[j].nombre) > 0)
					{
						if(listaEmpleados[i].sector < listaEmpleados[j].sector)
						{
							auxEmpleado = listaEmpleados[i];
							listaEmpleados[i] = listaEmpleados[j];
							listaEmpleados[j] = auxEmpleado;
						}
					}
				}
			}
			else
			{
				for(j=i+1;j<tam;j++)
				{
					if(strcmp(listaEmpleados[i].nombre, listaEmpleados[j].nombre) > 1)
					{
						auxEmpleado = listaEmpleados[i];
						listaEmpleados[i] = listaEmpleados[j];
						listaEmpleados[j] = auxEmpleado;
					}
					else if(strcmp(listaEmpleados[i].nombre, listaEmpleados[j].nombre) < 0)
					{
						if(listaEmpleados[i].sector > listaEmpleados[j].sector)
						{
							auxEmpleado = listaEmpleados[i];
							listaEmpleados[i] = listaEmpleados[j];
							listaEmpleados[j] = auxEmpleado;
						}
					}
				}
			}
		}
	}

	mostrarEmpleados(listaEmpleados, tam);

	return ret;
}

/**
 * @fn void totalYPromedioSalarios(eEmpleado*, int)
 * @brief funcion que calcula el total y el promedio de salarios y cuenta cuantos empleados superan el sueldo promedio
 *
 * @param listaEmpleados puntero que contiene el array de empleados
 * @param tam tamanio del array
 */
void totalYPromedioSalarios(eEmpleado* listaEmpleados, int tam)
{
	int total = 0;
	float promedio;
	int i;
	int totalEmpleados = 0;
	int j;
	int sueldoMayor = 0;

	if(listaEmpleados != NULL && tam > 0)
	{
		for(i=0;i<tam;i++)
		{
			if(listaEmpleados[i].isEmpty == OCUPADO)
			{
				totalEmpleados++;
				total += listaEmpleados[i].salario;
			}
		}
	}

	promedio = total / totalEmpleados;

	for(j=0;j<tam;j++)
	{
		if(promedio < listaEmpleados[j].salario)
		{
			sueldoMayor++;
		}
	}

	printf("El total de salarios es de: %d\n", total);
	printf("En promedio un empleado cobra: %.2f\n", promedio);
	if(sueldoMayor == 0)
	{
		printf("No hay empleados que cobren mas que el promedio\n");
	}
	else
	{
		printf("Hay %d empleado/os que cobra/an mas salario que el promedio.\n", sueldoMayor);
	}

}
