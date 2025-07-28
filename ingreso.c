//Librerías estándar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "ingreso.h"

//Declaración de constantes
#define MAX_LINEA 100
#define MAX_USUARIO 50
#define MAX_CLAVE 50
#define MAX_INTENTOS 3

// Función para leer contraseña mostrando asteriscos (Windows)
void leerContrasena(char *buffer, int max_len) {
	int i = 0;
	char c;
	while (1) {
		c = getch(); // Lee carácter sin mostrar en pantalla
		if (c == '\r' || c == '\n') { // Enter para terminar
			buffer[i] = '\0';
			printf("\n");
			break;
		} else if (c == '\b') { // Backspace
			if (i > 0) {
				i--;
				printf("\b \b"); // Borra el asterisco de pantalla
			}
		} else if (i < max_len - 1) {
			buffer[i++] = c;
			printf("*"); // Muestra asterisco
		}
	}
}

//Función para autentificar usuarios
int autenticar(const char *usuario, const char *clave) {
	FILE *archivo = fopen("usuarios.txt", "r");
	if (archivo == NULL) {
		perror("Error al abrir el archivo");
		return -1;  // -1: error de archivo
	}
	
	char linea[MAX_LINEA];
	while (fgets(linea, sizeof(linea), archivo)) {
		linea[strcspn(linea, "\n")] = 0;
		
		char *usuario_archivo = strtok(linea, ":");
		char *clave_archivo = strtok(NULL, ":");
		
		if (usuario_archivo && strcmp(usuario, usuario_archivo) == 0) {
			fclose(archivo);
			if (clave_archivo && strcmp(clave, clave_archivo) == 0)
				return 1; // Usuario y clave correctos
			else
				return 0; // Usuario correcto, clave incorrecta
		}
	}
	
	fclose(archivo);
	return 2; // Usuario no encontrado
}

//Función para registrar el Usuario
int registrarUsuario(const char *usuario, const char *clave) {
	FILE *archivo = fopen("usuarios.txt", "a"); // Abrir en modo añadir
	if (archivo == NULL) {
		perror("Error al abrir el archivo para registrar");
		return 0;
	}
	
	fprintf(archivo, "%s:%s\n", usuario, clave);
	fclose(archivo);
	
	limpiarPantalla();
	
	printf("\n --------Nuevo usuario del sistema: %s--------\n", usuario); 
	//Solicitar autenticación inmediata
	char usuarioIngreso[MAX_USUARIO];
	char claveIngreso[MAX_CLAVE];
	int intentos=0;
	int resultado;
	
	do{
		printf("\n Ingrese su usuario: ");
		scanf("%s", usuarioIngreso);
		
		printf("Ingrese su clave: ");
		leerContrasena(claveIngreso, MAX_CLAVE);
		
		resultado = autenticar(usuarioIngreso, claveIngreso);
		
		if (resultado == 1){
			printf("\n ，autentificación exitosa! Bienvenido de nuevo, %s. \n", usuarioIngreso);
			return 1;
		} else if (resultado == 0){
			limpiarPantalla();
			printf("\nClave incorrecta. Intente nuevamente. \n");
		}else if (resultado == 2){
			limpiarPantalla();
			printf("\nUsuario no encontrado. Intente nuevamente. \n");
		}
		
		intentos++;
	} while(intentos< MAX_INTENTOS);
	
	printf("\nNúmero máximo de intentos alcanzado. \n");
	return 0;
}
