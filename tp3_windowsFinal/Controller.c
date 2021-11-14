#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "validaciones.h"

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

	if(pArrayListEmployee != NULL)
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

    if(pArrayListEmployee != NULL)
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
 * @fn int controller_getEmployeeById(LinkedList*, int)
 * @brief
 *
 * @param pArrayListEmployee
 * @param index
 * @return
 */
int controller_getEmployeeById(LinkedList* pArrayListEmployee, int index)
{
	int idRet = -1;
	int len;
	int id;
	int i;
	Employee* empleado;

	len = ll_len(pArrayListEmployee);

	for(i=0;i<len;i++)
	{
		empleado = ll_get(pArrayListEmployee, i);
		employee_getId(empleado, &id);

		if(index == id)
		{
			idRet = i;
		}
	}

	return idRet;
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

    if(pArrayListEmployee != NULL)
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

    if(pArrayListEmployee != NULL)
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

	if(pArrayListEmployee != NULL)
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
	int i;
	int j;
	char nombre1[128];
	char nombre2[128];
	int len;
	int orden = 1;
	Employee* pEmpleado1 = NULL;
	Employee* pEmpleado2 = NULL;

	len = ll_len(pArrayListEmployee);

	if(pArrayListEmployee!= NULL)
	{
	   printf("Ingrese orden ascendente (1) o descendente (0): ");
	   fflush(stdin);
	   validarEntero(&orden, 0, 1);

	   for (i=0; i<len-1;i++)
	   {
	       for (j=i+1;j<len;j++)
	       {
	    	 pEmpleado1 = ll_get(pArrayListEmployee, i);
	    	 pEmpleado2 = ll_get(pArrayListEmployee, j);

	          if(pEmpleado1 != NULL && pEmpleado2 != NULL)
	          {
	        	  if(employee_getNombre(pEmpleado1, nombre1) &&
	                 employee_getNombre(pEmpleado2, nombre2))
	              {
	        		  if(orden)// ascendente
	        		  {
						  if(strcmp(nombre1, nombre2) > 0)
						  {
							  ll_set(pArrayListEmployee,i,pEmpleado2);
							  ll_set(pArrayListEmployee,j,pEmpleado1);
							  ret = 1;
						  }
	        		  }
	        		  else //descendente
	        		  {
						  if(strcmp(nombre1, nombre2) < 0)
						  {
							  ll_set(pArrayListEmployee,i,pEmpleado2);
							  ll_set(pArrayListEmployee,j,pEmpleado1);
							  ret = 1;
						  }
	        		  }
	              }
	           }
	        }
	    }
	   controller_ListEmployee(pArrayListEmployee);
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

    if(pArrayListEmployee != NULL && path != NULL)
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

    if(pArrayListEmployee != NULL && path != NULL)
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
