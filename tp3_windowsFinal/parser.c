#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile, LinkedList* pArrayListEmployee)
{
    int ret = 0;
    char id[128];
    char nombre[128];
    char horasTrabajadas[128];
    char sueldo[128];
    Employee* pEmpleado;

    if(pFile != NULL && pArrayListEmployee != NULL)
    {
        fscanf(pFile,"%s\n",nombre);
         while(!feof(pFile))
        {
           if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n] \n",id,nombre,horasTrabajadas,sueldo) == 4)
           {
               pEmpleado = employee_newParametrosStr(id,nombre,horasTrabajadas,sueldo);
               ll_add(pArrayListEmployee,pEmpleado);
           }
           else
           {
        	   printf("Error\n");
               break;
           }
        }
        ret = 1;
    }

    return ret;
}


/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile, LinkedList* pArrayListEmployee)
{
	int ret = 0;
    int devolucionFread;
    Employee* pEmpleado;

    fseek(pFile,33,SEEK_SET);
    while(!feof(pFile))
    {
        pEmpleado = employee_new();
        devolucionFread = fread(pEmpleado,sizeof(Employee),1,pFile);
        if(devolucionFread != 1)
        {
            break;
        }
        ll_add(pArrayListEmployee,pEmpleado);
        ret = 1;
    }
    return ret;
}
