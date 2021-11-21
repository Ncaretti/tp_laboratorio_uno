/*
 * Controller.c
 *
 *  Created on: Nov 20, 2021
 *      Author: Seether
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/Employee.h"
#include "../src/parser.h"
#include "../src/validaciones.h"

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	int ret = 0;

	FILE* pFile = fopen (path,"r");

	if(path != NULL && pArrayListEmployee != NULL)
	{
		if(pFile != NULL)
		{
			if(parser_EmployeeFromText(pFile, pArrayListEmployee))
			{
				ret = 1;
			}
		}
		fclose(pFile);
	}

    return ret;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int ret = 0;
	FILE* pFile = NULL;

	pFile = fopen(path,"rb");

	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		if(parser_EmployeeFromBinary(pFile, pArrayListEmployee))
		{
			ret = 1;
		}
	}
	fclose(pFile);

    return ret;
}

int controller_nuevoId(LinkedList* pArrayListEmployee)
{
	int mayorId = -1;
	int nuevoId;
	int len;
	int i;
	Employee* auxEmployee;

	if(ll_isEmpty(pArrayListEmployee) == 0)
	{
		len = ll_len(pArrayListEmployee);

		for(i=0;i<len;i++)
		{
			auxEmployee = (Employee*) ll_get(pArrayListEmployee, i);

			if(i == 0 || mayorId < auxEmployee->id)
			{
				mayorId = auxEmployee->id;
			}
		}
	}

	nuevoId = mayorId + 1;

	return nuevoId;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
    int ret = -1;
    int id;
    char nombre[128];
    int horasTrabajadas;
    int sueldo;

    Employee* nuevoEmpleado;

    if(ll_isEmpty(pArrayListEmployee) == 0)
    {
    	id = controller_nuevoId(pArrayListEmployee);
    	printf("El empleado tendra el ID: %d\n", id);

		//NOMBRE//
    	getNombre(nombre, 128, 5, "Ingrese el nombre: ", "Error, ingrese un nombre valido.");

		//HORAS TRABAJADAS//
		printf("Ingrese horas trabajadas: ");
		fflush(stdin);
		validarEntero(&horasTrabajadas, 1, 10000000);

		//SALARIO//
		printf("Ingrese salario: ");
		fflush(stdin);
		validarEntero(&sueldo, 1, 200000000);

		ret = 1;
		nuevoEmpleado = employee_newParametros(&id, nombre, &horasTrabajadas, &sueldo);
    }

    if(ret == 1)
    {
    	ret = ll_add(pArrayListEmployee, nuevoEmpleado);
    }

    return ret;
}

/**
 * @fn int controller_ListEmployee(LinkedList*)
 * @brief
 *
 * @param pArrayListEmployee
 * @return
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    int id;
    char nombre[128];
    int horasTrabajadas;
    int sueldo;
    int contEmpleados = 0;
    int ret = 0;
    int len;
    int i;
    Employee* pEmpleado;

    if(ll_isEmpty(pArrayListEmployee) == 0)
    {

    	len = ll_len(pArrayListEmployee);

        printf("  ID   NOMBRE    HORAS    SUELDO\n");

        for(i=0; i<len; i++)
        {
        	pEmpleado = (Employee*) ll_get(pArrayListEmployee, i);
            if(employee_getId(pEmpleado, &id) &&
                    employee_getNombre(pEmpleado, nombre) &&
                    employee_getHorasTrabajadas(pEmpleado, &horasTrabajadas) &&
                    employee_getSueldo(pEmpleado, &sueldo))
            {
                printf("%4d    %-10s%-3d      %d\n", pEmpleado->id, pEmpleado->nombre, pEmpleado->horasTrabajadas, pEmpleado->sueldo);
                contEmpleados++;
            }
        }
        if(contEmpleados == len)
        {
        	ret = 1;
        }
    }
    return ret;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    int ret = 0;
    int opcionLista;
    int id;
    int i;
    char nuevoNombre [128];
    int nuevoHorasTrabajo;
    int nuevoSueldo;
    int auxId;
    int len;
    int opcion;
    Employee* pEmpleado = NULL;

    if(ll_isEmpty(pArrayListEmployee) == 0)
    {
        len = ll_len(pArrayListEmployee);

        printf("Desea ver la lista de empleados? 1(si)/2(no)");
        fflush(stdin);
        validarEntero(&opcionLista,1,2);

        if(opcionLista == 1)
        {
        	controller_ListEmployee(pArrayListEmployee);
        }
        else
        {
        	printf("Ha elegido no ver la lista.\n");
        }

        printf("Ingrese el ID del empleado a modificar: ");
           if(validarEntero(&id,1,len))
           {
               for(i=0; i<len; i++)
               {
               	pEmpleado = (Employee*)ll_get(pArrayListEmployee, i);
                   if(employee_getId(pEmpleado, &auxId))
                   {
                       if(auxId == id)
                       {
                           if(employee_getNombre(pEmpleado, nuevoNombre)
                              && employee_getHorasTrabajadas(pEmpleado, &nuevoHorasTrabajo)
						      && employee_getSueldo(pEmpleado, &nuevoSueldo))
                           {
                            do
                            {
								printf("\nMENU MODIFICACIONES:\n"
									   "1- Modificar nombre\n"
									   "2- Modificar horas trabajadas\n"
									   "3- Modificar sueldo\n"
									   "4- Salir\n");
								validarEntero(&opcion, 1, 4);

								switch(opcion)
								{
									case 1:
										if (getNombre(nuevoNombre, 128, 5, "Ingrese el nuevo nombre: ", "Error, ingrese un nombre valido"))
										{
											if(employee_setNombre(pEmpleado, nuevoNombre))
											{
												ret = 1;
											}
										}
									break;

									case 2:
										printf("Ingrese las nuevas horas de trabajo: ");
										if(validarEntero(&nuevoHorasTrabajo,1,1000000))
										{
											if(employee_setHorasTrabajadas(pEmpleado, nuevoHorasTrabajo))
											{
												ret = 1;
											}
										}
									break;

									case 3:
										printf("Ingrese el nuevo sueldo: ");
										if(validarEntero(&nuevoSueldo,1,20000000))
										{
											if(employee_setSueldo(pEmpleado, nuevoSueldo))
											{
												ret = 1;
											}
										}
									break;

									case 4:
										printf("Ha salido con exito del menu de modificaciones.\n");
									break;
								}
                           	}while(opcion != 4);
                           }
                       }
                   }
               }
           }
        }

    return ret;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int ret = -1;
	int opcionLista;
	int opcion;
	int idIngresado;
	int i;
	char nuevoNombre [128];
	int nuevoHorasTrabajo;
	int nuevoSueldo;
	int auxId;
	int len;
	Employee* pEmpleado = NULL;

	if(ll_isEmpty(pArrayListEmployee) == 0)
	{
	    len = ll_len(pArrayListEmployee);

	    printf("Desea ver la lista de empleados? 1(si)/2(no)");
	    fflush(stdin);
	    validarEntero(&opcionLista,1,2);

	    if(opcionLista == 1)
	    {
	    	controller_ListEmployee(pArrayListEmployee);
	    }
	    else
	    {
	        printf("Ha elegido no ver la lista.\n");
	    }

	    printf("Ingrese el ID del empleado a modificar: ");
	    if(validarEntero(&idIngresado,1,len))
	    {
	       for(i=0; i<len; i++)
	       {
	          pEmpleado = (Employee*)ll_get(pArrayListEmployee, i);
	          if(employee_getId(pEmpleado, &auxId))
	          {
	        	  if(auxId == idIngresado)
	        	  {
					  if(employee_getNombre(pEmpleado, nuevoNombre)
						 && employee_getHorasTrabajadas(pEmpleado, &nuevoHorasTrabajo)
						 && employee_getSueldo(pEmpleado, &nuevoSueldo))
					  {
						 printf("\n**********************************\n");
						 printf("%d   %s   %d   %d\n", pEmpleado->id, pEmpleado->nombre, pEmpleado->horasTrabajadas, pEmpleado->sueldo);
						 printf("**********************************\n");

						 printf("Desea eliminar a este empleado? 1(si)/2(no): ");
						 validarEntero(&opcion, 1, 2);

						 if(opcion)
						 {
							 ll_remove(pArrayListEmployee, i);
							 ret = 1;
						 }
						 else
						 {
							 printf("Ha cancelado la operacion.\n");
						 }
					  }
	        	  }
	          }
	       }
	    }
	}
	return ret;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int ret = -1;
	int opcion;
	int opcionOrden;

	if(ll_isEmpty(pArrayListEmployee) == 0)
	{
		do
		{
			printf("\nMENU ORDENAMIENTO:\n"
					   "1. Ordenar por ID\n"
					   "2. Ordenar por horas de trabajo\n"
					   "3. Ordenar por nombre\n"
					   "4. Ordenar por sueldo\n"
					   "5. Salir\n");
			validarEntero(&opcion, 1, 5);

			if(opcion != 5)
			{
				printf("Orden ascendete(1) o descendente(0)?: \n");
				validarEntero(&opcionOrden, 0, 1);
			}

			switch(opcion)
			{
				case 1:
					printf("Sorteando por ID...\n");
					ll_sort(pArrayListEmployee, employee_compareByID, opcionOrden);
					controller_ListEmployee(pArrayListEmployee);
				break;

				case 2:
					printf("Sorteando por Horas Trabajadas...\n");
					ll_sort(pArrayListEmployee, employee_compareByHorasTrabajadas, opcionOrden);
					controller_ListEmployee(pArrayListEmployee);
				break;

				case 3:
					printf("Sorteando por Nombre...\n");
					ll_sort(pArrayListEmployee, employee_compareByNombre, opcionOrden);
					controller_ListEmployee(pArrayListEmployee);
				break;

				case 4:
					printf("Sorteando por Sueldo...\n");
					ll_sort(pArrayListEmployee, employee_compareBySueldo, opcionOrden);
					controller_ListEmployee(pArrayListEmployee);
				break;

				case 5:
					printf("Ha salido con exito.\n");
				break;
			}
		}while(opcion != 5);
	}

	return ret;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int len;
    int i;
    FILE* pFile;
    Employee* auxEmployee = NULL;

    int idStr;
    char nombreStr[51];
    int horasTrabajadasStr;
    int sueldoStr;

    if(ll_isEmpty(pArrayListEmployee) == 0 && path != NULL)
    {
        pFile = fopen(path, "w");//abro el archivo en modo escritura
        len = ll_len(pArrayListEmployee);

        if(pFile != NULL)
        {
            fprintf(pFile, "Id,Nombre,Horas trabajadas,Salario\n");
            for(i=0; i<len; i++)
            {
                auxEmployee = (Employee*) ll_get(pArrayListEmployee, i);
                employee_getId(auxEmployee, &idStr);
                employee_getNombre(auxEmployee, nombreStr);
                employee_getHorasTrabajadas(auxEmployee, &horasTrabajadasStr);
                employee_getSueldo(auxEmployee, &sueldoStr);

                fprintf(pFile, "%d,%s,%d,%d\n", idStr, nombreStr, horasTrabajadasStr, sueldoStr);
            }
        }
        fclose(pFile);
        retorno = 0;
    }
    return retorno;
}


/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int len;
    int i;
    FILE* pFile;
    Employee* auxEmployee = NULL;

    if(ll_isEmpty(pArrayListEmployee) == 0 && path != NULL)
    {
        pFile = fopen(path, "wb");
        len = ll_len(pArrayListEmployee);

        if(pFile != NULL)
        {
            for(i=0; i<len; i++)
            {
                auxEmployee = (Employee*) ll_get(pArrayListEmployee, i);
                fwrite(auxEmployee, sizeof(Employee), 1, pFile);
            }
        }
        fclose(pFile);
        retorno = 0;
    }

    return retorno;
}

int controller_clearDeleteListEmployee(LinkedList* pArrayListEmployee)
{
	int ret = -1;
	int opcionAsegurar;
	int opcion;


	printf("\n1. Limpiar la lista de empleados\n"
		   "2. Eliminar la lista de empleados\n"
		   "3. Salir.\n");
	fflush(stdin);
	validarEntero(&opcion, 1, 3);

	switch(opcion)
	{
		case 1:
			printf("CUIDADO esta por LIMPIAR todos los empleados de la lista, esta seguro? 1(si)/2(no)\n");
			fflush(stdin);
			if(validarEntero(&opcionAsegurar, 1, 2))
			{
				if(opcionAsegurar)
				{
					ll_clear(pArrayListEmployee);
					printf("Ha vaciado la lista con exito.\n");
					ret = 1;
				}
				else
				{
					printf("Ha cancelado la accion.\n");
					ret = 0;
				}
			}
		break;

		case 2:
			printf("CUIDADO esta por ELIMINAR la lista de empleados, esta seguro? 1(si)/2(no)\n");
			fflush(stdin);
			if(validarEntero(&opcionAsegurar, 1, 2))
			{
				if(opcionAsegurar)
				{
					ll_deleteLinkedList(pArrayListEmployee);
					printf("Ha eliminado la lista con exito.\n");
					ret = 1;
				}
				else
				{
					printf("Ha cancelado la accion.\n");
					ret = 0;
				}
			}
		break;

		case 3:
			printf("Ha salido con exito.\n");
		break;

	}
	return ret;
}

int controller_listFilter(LinkedList* pArrayListEmployee)
{
	int ret = 0;
	int opcion;
	int opcionOrden;

	if(ll_isEmpty(pArrayListEmployee) == 0)
	{
		do
		{
			printf("\nMENU ORDENAMIENTO:\n"
					   "1. Filtrar por ID\n"
					   "2. Filtrar por horas de trabajo\n"
					   "3. Filtrar por sueldo\n"
					   "4. Salir\n");
			validarEntero(&opcion, 1, 4);

			switch(opcion)
			{
				case 1:
					printf("\n1. IDs pares.\n"
						   "2. IDs impares.\n");
					validarEntero(&opcionOrden, 1, 2);

					if(opcionOrden == 1)
					{
						LinkedList* listaIdPar = ll_filter(pArrayListEmployee, employee_filterByIDPar);
						controller_ListEmployee(listaIdPar);
						ll_deleteLinkedList(listaIdPar);
					}
					else
					{
						LinkedList* listaIdImpar = ll_filter(pArrayListEmployee, employee_filterByIDImpar);
						controller_ListEmployee(listaIdImpar);
						ll_deleteLinkedList(listaIdImpar);
					}
				break;

				case 2:
					printf("\n1. Horas Trabajadas mayores a 100.\n"
						   "2. Horas Trabajadas menores a 100.\n");
					validarEntero(&opcionOrden, 1, 2);

					if(opcionOrden == 1)
					{
						LinkedList* listaHorasTrabajadasMayores = ll_filter(pArrayListEmployee, employee_filterByHorasTrabajadasMayores);
						controller_ListEmployee(listaHorasTrabajadasMayores);
						ll_deleteLinkedList(listaHorasTrabajadasMayores);
					}
					else
					{
						LinkedList* listaHorasTrabajadasMenores = ll_filter(pArrayListEmployee, employee_filterByHorasTrabajadasMenores);
						controller_ListEmployee(listaHorasTrabajadasMenores);
						ll_deleteLinkedList(listaHorasTrabajadasMenores);
					}

				break;

				case 3:
					printf("\n1. Sueldos mayores a $30.000.\n"
						   "2. Sueldos menores a $30.000\n");
					validarEntero(&opcionOrden, 1, 2);

					if(opcionOrden == 1)
					{
						LinkedList* listaSueldoMayor = ll_filter(pArrayListEmployee, employee_filterBySueldoMayor);
						controller_ListEmployee(listaSueldoMayor);
						ll_deleteLinkedList(listaSueldoMayor);
					}
					else
					{
						LinkedList* listaSueldoMenor = ll_filter(pArrayListEmployee, employee_filterBySueldoMenor);
						controller_ListEmployee(listaSueldoMenor);
						ll_deleteLinkedList(listaSueldoMenor);
					}

				break;

				case 4:
					printf("Ha salido con exito.\n");
				break;
			}
		}while(opcion != 5);
	}
	return ret;
}
