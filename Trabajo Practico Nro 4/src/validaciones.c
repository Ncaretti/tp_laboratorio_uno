/*
 * validaciones.c
 *
 *  Created on: Nov 20, 2021
 *      Author: Seether
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validaciones.h"

int validarEntero(int* datoValidar, int minimo, int maximo)
{
	int validacion = 0;

	fflush(stdin);
	if((scanf("%d", datoValidar)))
	{
		if(*datoValidar >= minimo && *datoValidar <= maximo)
		{
			validacion = 1;
		}
		else
		{
			do
			{
				printf("Error, ingrese un valor valido: ");
				fflush(stdin);
				if(scanf("%d", datoValidar))
				{
					if(*datoValidar >= minimo && *datoValidar <= maximo)
					{
						validacion = 1;
					}
				}
				else
				{
					validacion = 0;
				}
			}while(validacion == 0);
		}
	}
	else
	{
		do
		{
			printf("Error, ingrese un valor valido: ");
			fflush(stdin);
			if(scanf("%d", datoValidar))
			{
				if(*datoValidar >= minimo && *datoValidar <= maximo)
				{
					validacion = 1;
				}
			}
			else
			{
				validacion = 0;
			}

		}while(validacion == 0);
	}

	return validacion;
}


int getNombre(char nombre[], int len, int intentos, char mensaje[], char mensajeError[])
{
    int i;
    char auxNombre[100];
    int todoOk = 0;
    int flag = 0;
    if (nombre != NULL && mensaje != NULL && mensajeError != NULL && intentos >= 0)
    {
        do
        {
            printf("%s", mensaje);
            fflush(stdin);
            gets(auxNombre);

            i = 0;
            while (auxNombre[i] != '\0')
            {
                if ((auxNombre[i] < 'a' || auxNombre[i] > 'z') && (auxNombre[i] < 'A' || auxNombre[i] > 'Z'))
                {
                    flag = 1;
                    break;
                }
                else
                {
                    flag = 0;
                    i++;
                }
            }

            if (strlen(auxNombre) < len && !flag)
            {
                strncpy(nombre, auxNombre,len-1);
                break;
            }

            printf("%s", mensajeError);
            intentos--;
        } while (intentos);

        if (intentos > 0)
        {
            todoOk = 1;
        }
    }
    return todoOk;
}




