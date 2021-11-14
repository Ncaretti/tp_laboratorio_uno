#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "parser.h"
#include "validaciones.h"

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
	setbuf(stdout, NULL);
    int option = 0;
    int retEdit;
    int flagEmpleados = 0;
    int flagCambiosEmpleado = 0;
    int flagBinPrimero = 0;
    int flagAberturaData = 1;

    LinkedList* listaEmpleados = ll_newLinkedList();

    do{
        printf("Menu:\n"
       		 "1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).\n"
       		 "2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).\n"
       		 "3. Alta de empleado\n"
       		 "4. Modificar datos de empleado\n"
       		 "5. Baja de empleado\n"
       		 "6. Listar empleados\n"
       		 "7. Ordenar empleados (solo alfabeticamente)\n"
       		 "8. Guardar los datos de los empleados en el archivo data.csv (modo texto).\n"
       		 "9. Guardar los datos de los empleados en el archivo data.csv (modo binario).\n"
       		 "10. Salir\n");
        scanf("%d", &option);

        switch(option)
        {
            case 1:
            	if(flagAberturaData)
            	{
					if(controller_loadFromText("data.csv", listaEmpleados))
					{
						printf("El archivo se cargo con exito.\n");
						flagEmpleados = 1;
						flagBinPrimero = 1;
						flagAberturaData = 0;
					}
					else
					{
						printf("Hubo un error al cargar el archivo.\n");
					}
            	}
            	else
            	{
            		printf("Ya se han cargado los datos.\n");
            	}
            	system("pause");
            break;

            case 2:
            	if(flagBinPrimero)
            	{
					if(controller_loadFromBinary("data.bin", listaEmpleados))
					{
						printf("El archivo binario se cargo con exito.\n");
						flagEmpleados = 1;
					}
					else
					{
						printf("Hubo un error al cargar el archivo binario o no se ha generado un archivo .bin.\n");
					}
            	}
            	else
            	{
            		printf("No se ha generado ningun archivo .bin\n");
            	}
            	system("pause");
            break;

            case 3:
            	if(controller_addEmployee(listaEmpleados) != -1)
            	{
            		printf("Empleado creado con exito.\n");
            		flagEmpleados = 1;
            	}
            	else
            	{
            		printf("Hubo un error al crear el empleado.\n");
            	}
            	system("pause");
            break;

            case 4:
            	if(flagEmpleados)
            	{
					retEdit = controller_editEmployee(listaEmpleados);
					if(retEdit)
					{
						printf("Cambio/s realizado/s con exito.\n");
						flagCambiosEmpleado = 1;
					}
					else if(retEdit == 0)
					{
						printf("No se realizaron cambios.\n");
					}
					else if(retEdit == -1)
					{
						printf("Hubo un error al realizar un cambio.\n");
					}
            	}
            	else
            	{
            		printf("No hay empleados cargados.\n");
            	}

				system("pause");
            break;

            case 5:
            	if(flagEmpleados)
            	{
					if(controller_removeEmployee(listaEmpleados))
					{
						printf("Empleado removido con exito.\n");
						flagCambiosEmpleado = 1;
					}
					else
					{
						printf("Ocurrio un error al remover el empleado.\n");
					}
            	}
            	else
				{
            		printf("No hay empleados cargados.\n");
				}
            	system("pause");
            break;

            case 6:
            	if(flagEmpleados)
            	{
            		controller_ListEmployee(listaEmpleados);
            	}
            	else
				{
            		printf("No hay empleados cargados.\n");
				}
            	system("pause");
            break;

            case 7:
            	if(flagEmpleados)
            	{
            		controller_sortEmployee(listaEmpleados);
            	}
            	else
            	{
            		printf("No hay empleados cargados.\n");
            	}
            	system("pause");
            break;

            case 8:
            	if(flagCambiosEmpleado)
            	{
            		controller_saveAsText("data.csv", listaEmpleados);
            		flagAberturaData = 1;
            	}
            	else
            	{
            		printf("No se hicieron cambios, no es posible guardar.\n");
            	}
            	system("pause");
            break;

            case 9:
            	if(flagCambiosEmpleado || flagBinPrimero)
            	{
            		controller_saveAsBinary("data.bin", listaEmpleados);
            	}
            	else
            	{
            		printf("No se hicieron cambios o no se abrio el .csv, no es posible guardar.\n");
            	}
            	system("pause");
            break;

            case 10:
            	printf("Ha salido con exito, gracias por usar la aplicacion.\n");
            	system("pause");
            break;

            default:
            	printf("Error, ingrese una opcion valida.\n");
            	system("pause");
            break;
        }
    }while(option != 10);
    return 0;
}

