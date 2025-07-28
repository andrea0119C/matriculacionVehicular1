//Librerías estándar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Declaración de constantes
#define MAX_LINEA 100
#define MAX_USUARIO 50
#define MAX_CLAVE 50
#define MAX_INTENTOS 3

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

//Función registrar usuario
int registrar_usuario(const char *usuario, const char *clave) {
	FILE *archivo = fopen("usuarios.txt", "a"); // Abrir en modo añadir
	if (archivo == NULL) {
		perror("Error al abrir el archivo para registrar");
		return 0;
	}
	
	fprintf(archivo, "%s:%s\n", usuario, clave);
	fclose(archivo);
	return 1;
}

//Cuerpo del programa
int main() {
	char usuario[MAX_USUARIO], clave[MAX_CLAVE];
	int intentos = 0;
	int resultado;
	
	printf("Usuario: ");
	scanf("%s", usuario);
	
	while (intentos < MAX_INTENTOS) {
		printf("Clave: ");
		scanf("%s", clave);
		
		resultado = autenticar(usuario, clave);
		
		//Validación de contraseña
		if (resultado == 1) {
			printf("Autenticación exitosa. Bienvenido, %s.\n", usuario);
			return 0;
		} else if (resultado == 0) {
			printf("Clave incorrecta. Intento %d de %d.\n", ++intentos, MAX_INTENTOS);
		} else if (resultado == 2) {
			printf("Usuario no encontrado,¿Deseas registrarte como '%s'? (s/n): ", usuario);//Añadir un nuevo usuario
			char opcion;
			scanf(" %c", &opcion);
			if (opcion == 's' || opcion == 'S') {
				printf("Elige una clave: ");
				scanf("%s", clave);
				if (registrar_usuario(usuario, clave)) {
					printf("Usuario registrado exitosamente.\n");
				} else {
					printf("Error al registrar usuario.\n");
				}
			}
			return 0;
		} else {
			return 1; // Error general
		}
	}
	
	printf("Demasiados intentos fallidos. Acceso bloqueado.\n");//Bloque de acceso
	return 1;
}
