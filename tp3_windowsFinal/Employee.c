#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"


Employee* employee_new()
{
	Employee* nuevoEmpleado;

	nuevoEmpleado = (Employee*) malloc(sizeof(Employee));

	if(nuevoEmpleado != NULL)
	{
		nuevoEmpleado->horasTrabajadas = 0;
		nuevoEmpleado->id = 0;
		strcpy(nuevoEmpleado->nombre, "NN");
		nuevoEmpleado->sueldo = 0;
	}

	return nuevoEmpleado;
}

Employee* employee_newParametrosStr(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr)
{
	Employee* nuevoEmpleadoStr = employee_new();

	if(nuevoEmpleadoStr != NULL)
	{
		if(!(employee_setId(nuevoEmpleadoStr, atoi(idStr))
			&& employee_setNombre(nuevoEmpleadoStr, nombreStr)
			&& employee_setHorasTrabajadas(nuevoEmpleadoStr, atoi(horasTrabajadasStr))
			&& employee_setSueldo(nuevoEmpleadoStr, atoi(sueldoStr))))
		{
			printf("Hubo un error.\n");
			employee_delete(nuevoEmpleadoStr);
		}
	}

	return nuevoEmpleadoStr;
}

Employee* employee_newParametros(int* id, char* nombre, int* horasTrabajadas, int* sueldo)
{
	Employee* nuevoEmpleadoP = employee_new();

	if(nuevoEmpleadoP != NULL)
	{
		if(!(employee_setId(nuevoEmpleadoP, *id)
			&& employee_setNombre(nuevoEmpleadoP, nombre)
			&& employee_setHorasTrabajadas(nuevoEmpleadoP, *horasTrabajadas)
			&& employee_setSueldo(nuevoEmpleadoP, *sueldo)))
		{
			printf("Hubo un error.\n");
			employee_delete(nuevoEmpleadoP);
		}
	}

	return nuevoEmpleadoP;
}

//--------------DELETE------------//

void employee_delete(Employee* this)
{
	if(this != NULL)
	{
		free(this);
		this = NULL;
	}
}

//-------------SETTERS-------------//

int employee_setId(Employee* this,int id)
{
	int ret = 0;

	if(this != NULL)
	{
		this->id = id;
		ret = 1;
	}

	return ret;
}

int employee_setNombre(Employee* this,char* nombre)
{
	int ret = 0;

	if(this != NULL)
	{
		strcpy(this->nombre, nombre);
		ret = 1;
	}

	return ret;
}

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
	int ret = 0;

	if(this != NULL)
	{
		this->horasTrabajadas = horasTrabajadas;
		ret = 1;
	}

	return ret;
}

int employee_setSueldo(Employee* this,int sueldo)
{
	int ret = 0;

	if(this != NULL)
	{
		this->sueldo = sueldo;
		ret = 1;
	}

	return ret;
}


//----------------GETTERS-------------//

int employee_getId(Employee* this,int* id)
{
	int ret = 0;

	if(this != NULL && id != NULL)
	{
		*id = this->id;
		ret = 1;
	}

	return ret;
}

int employee_getNombre(Employee* this,char* nombre)
{
	int ret = 0;

	if(this != NULL && nombre != NULL)
	{
		strcpy(nombre, this->nombre);
		ret = 1;
	}

	return ret;
}

int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
	int ret = 0;

	if(this != NULL && horasTrabajadas != NULL)
	{
		*horasTrabajadas = this->horasTrabajadas;
		ret = 1;
	}
	return ret;
}

int employee_getSueldo(Employee* this,int* sueldo)
{
	int ret = 0;

	if(this != NULL && sueldo != NULL)
	{
		*sueldo = this->sueldo;
		ret = 1;
	}

	return ret;
}



