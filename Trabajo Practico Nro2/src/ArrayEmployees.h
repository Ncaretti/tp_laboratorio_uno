#ifndef ARRAYEMPLOYEES_H_
#define ARRAYEMPLOYEES_H_

typedef struct
{
	int id;
	char nombre[51];
	char apellido[51];
	float salario;
	int sector;
	int isEmpty;

}eEmpleado;

int iniciarEmpleados(eEmpleado* listaEmpleados, int tam);
int buscarLibre(eEmpleado* listaEmpleados, int tam);
int agregarEmpleado(eEmpleado* listaEmpleados, int tam, int* id, char nombre[], char apellido[], float* salario, int* sector);
void mostrarEmpleado(eEmpleado miEmpleado);
int mostrarEmpleados(eEmpleado* listaEmpleados, int tam);
int buscarEmpleadoPorId(eEmpleado* listaEmpleados, int tam, int id);
int modificarEmpleado(eEmpleado* listaEmpleados, int tam);
int removerEmpleado(eEmpleado* listaEmpleados, int tam);
int clasificarEmpleadosPorNombre(eEmpleado* listaEmpleados, int tam, int orden);
void totalYPromedioSalarios(eEmpleado* listaEmpleados, int tam);


#endif /* ARRAYEMPLOYEES_H_ */
