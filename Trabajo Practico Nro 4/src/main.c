/*
    utest example : Unit test examples.
    Copyright (C) <2018>  <Mauricio Davila>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../testing/inc/main_test.h"
#include "../inc/LinkedList.h"
#include "Controller.h"
#include "parser.h"
#include "validaciones.h"
#include "Employee.h"


int main(void)
{
	/*startTesting(1);  // ll_newLinkedList
	startTesting(2);  // ll_len
	startTesting(3);  // getNode - test_getNode
	startTesting(4);  // addNode - test_addNode
	startTesting(5);  // ll_add
	startTesting(6);  // ll_get
	startTesting(7);  // ll_set
	startTesting(8);  // ll_remove
	startTesting(9);  // ll_clear
	startTesting(10); // ll_deleteLinkedList
	startTesting(11); // ll_indexOf
	startTesting(12); // ll_isEmpty
	startTesting(13); // ll_push
	startTesting(14); // ll_pop
	startTesting(15); // ll_contains
	startTesting(16); // ll_containsAll
	startTesting(17); // ll_subList
	startTesting(18); // ll_clone
	startTesting(19); // ll_sort*/

	setbuf(stdout, NULL);
    int option = 0;
    int retEdit;
    int retClear;

    int flagEmpleados = 0;
    int flagCambiosEmpleado = 0;
    int flagBinPrimero = 0;
    int flagAberturaData = 1;
    int flagListaVaciada = 0;

    LinkedList* listaEmpleados = ll_newLinkedList();

    do{
        printf("Menu:\n"
       		 "1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).\n"
       		 "2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).\n"
       		 "3. Alta de empleado\n"
       		 "4. Modificar datos de empleado\n"
       		 "5. Baja de empleado\n"
       		 "6. Listar empleados\n"
       		 "7. Ordenar empleados\n"
       		 "8. Guardar los datos de los empleados en el archivo data.csv (modo texto).\n"
       		 "9. Guardar los datos de los empleados en el archivo data.csv (modo binario).\n"
        	 "10. Vaciar la lista de empleados o eliminar la lista.\n"
        	 "11. Crear lista por filtros.\n"
       		 "12. Salir\n");
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
            	if(flagEmpleados)
            	{
					if(controller_addEmployee(listaEmpleados) != -1)
					{
						printf("Empleado creado con exito.\n");
						flagEmpleados = 1;
					}
					else
					{
						printf("Hubo un error al crear el empleado.\n");
					}
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
            	if(flagEmpleados && flagListaVaciada == 0)
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
            	if(flagEmpleados && flagListaVaciada == 0)
            	{
					retClear = controller_clearDeleteListEmployee(listaEmpleados);

					if(retClear == -1)
					{
						printf("Ha ocurrido un error al limpiar/eliminar la lista.\n");
					}
					else if(retClear)
					{
						flagListaVaciada = 1;
					}
            	}
            	else
				{
            		printf("No hay empleados cargados.\n");
				}
            	system("pause");
            break;

            case 11:
            	if(flagEmpleados)
            	{
            		controller_listFilter(listaEmpleados);
            	}
            	else
				{
            		printf("No hay empleados cargados.\n");
				}
            	system("pause");
            break;

            case 12:
            	printf("Ha salido con exito, gracias por usar la aplicacion.\n");
            	system("pause");
            break;

            default:
            	printf("Error, ingrese una opcion valida.\n");
            	system("pause");
            break;
        }
    }while(option != 11);
    return 0;
}

































