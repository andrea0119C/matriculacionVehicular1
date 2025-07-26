//Librer�as est�ndar
#include <stdio.h>
#include <string.h>
#include "bloqueo.h"
#include "ingreso.h"

//Declaraci�n de variables
int realizadoOpcion1 = 0;
int realizadoOpcion2 = 0;
int realizadoOpcion3 = 0;
int realizadoOpcion4 = 0;

//Funci�n para imprimir centrado el texto
void imprimirCentrado(const char* texto) {
	int ancho = 80;
	int espacios = (ancho - strlen(texto)) / 2;
	for (int i = 0; i < espacios; i++) {
		printf(" ");
	}
	printf("%s\n", texto);
}

//Funci�n de bloqueo
int validarOpcion2(){
	if (!realizadoOpcion1){
		imprimirCentrado("Primero debe realizar opcion 1.\n");
		pausa();
		return 0;
	}
	return 1;
}
	
int validarOpcion3(){
	if (!realizadoOpcion2){
		imprimirCentrado("Primero debe realizar opcion 2.\n");
		pausa();
		return 0;
		}
	return 1;
}

int validarOpcion4(){
	if (!realizadoOpcion3){
		imprimirCentrado("Primero debe realizar opcion 3.\n");
		pausa();
		return 0;
	}
	return 1;
}

