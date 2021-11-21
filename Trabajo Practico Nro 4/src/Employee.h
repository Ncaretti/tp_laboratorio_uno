/*
 * Employee.h
 *
 *  Created on: Nov 20, 2021
 *      Author: Seether
 */
#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
#include "../inc/LinkedList.h"

typedef struct
{
    int id;
    char nombre[128];
    int horasTrabajadas;
    int sueldo;
}Employee;

Employee* employee_new();
Employee* employee_newParametrosStr(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr);
Employee* employee_newParametros(int* id,char* nombre,int* horasTrabajadas, int* sueldo);
void employee_delete(Employee* this);

int employee_setId(Employee* this,int id);
int employee_getId(Employee* this,int* id);

int employee_setNombre(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);

int employee_setSueldo(Employee* this,int sueldo);
int employee_getSueldo(Employee* this,int* sueldo);

int employee_compareByID(void* empleado1, void* empleado2);
int employee_compareByHorasTrabajadas(void* empleado1, void* empleado2);
int employee_compareByNombre(void* empleado1, void* empleado2);
int employee_compareBySueldo(void* empleado1, void* empleado2);

int employee_filterByIDPar(void* empleado);
int employee_filterByIDImpar(void* empleado);
int employee_filterByHorasTrabajadasMayores(void* empleado);
int employee_filterByHorasTrabajadasMenores(void* empleado);
int employee_filterBySueldoMayor(void* empleado);
int employee_filterBySueldoMenor(void* empleado);

#endif // employee_H_INCLUDED
