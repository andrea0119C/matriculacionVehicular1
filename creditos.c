//Librerías estándar
#include <stdio.h>
#include <string.h>
#include "creditos.h"
#include <unistd.h> // Para usleep
#include <conio.h>  // Para getch
#include <windows.h>

void mostrarCreditos() {
	// Suponemos un ancho de consola estándar de 80 caracteres
	const int ANCHO_CONSOLA = 80;
	
	printf("\n\n");
	printf("  ¦¦¦¦¦¦+    ¦¦¦¦¦¦+   ¦¦+       ¦¦+  ¦¦¦¦¦¦+   ¦¦¦¦¦¦+   ¦¦+  ¦¦+   ¦¦  +¦¦¦¦¦¦+\n");
	printf("  ¦¦+--¦¦+  ¦¦+---¦¦+  ¦¦¦       ¦¦¦  ¦¦+--¦¦+  ¦¦+--¦¦+  ¦¦¦  ¦¦¦   ¦¦  ¦¦¦+----+\n");
	printf("  ¦¦¦¦¦¦++  ¦¦¦   ¦¦¦  ¦¦¦       ¦¦¦  ¦¦¦  ¦¦¦  ¦¦¦¦¦¦++  ¦¦¦  ¦¦¦   ¦¦  ¦¦¦¦¦¦+  \n");
	printf("  ¦¦+---+   ¦¦¦   ¦¦¦  ¦¦¦       ¦¦¦  ¦¦¦  ¦¦¦  ¦¦+--¦¦+  ¦¦¦  +¦¦+ ¦¦+  +¦¦+--+  \n");
	printf("  ¦¦¦       +¦¦¦¦¦¦+  +¦¦¦¦¦¦¦+  ¦¦¦  ¦¦¦¦¦¦++  ¦¦¦  ¦¦¦  ¦¦¦  +¦¦¦¦++   ¦¦¦¦¦¦¦+\n");
	printf("  +-+        +-----+   +------+  +-+  +-----+   +-+  +-+  +-+   +---+    +------+\n");
	printf("\n");
	
	// Centrar el título "EQUIPO DE DESARROLLO"
	int titulo_len = strlen("EQUIPO DE DESARROLLO");
	int espacios_titulo = (ANCHO_CONSOLA - titulo_len) / 2;
	for(int i = 0; i < espacios_titulo; i++) printf(" ");
	printf("EQUIPO DE DESARROLLO\n\n");
	
	// Datos del equipo
	const char *nombres[] = {"Andrea Cumbal", "Paola Pacheco", "Valeria Chavez", "Anthony Jaramillo"};
	const char *roles[] = {"Scrum Master", "Product Owner", "Document manager", "QA Developer"};
	
	for(int i = 0; i < 4; i++) {
		// Calcular espacios para centrar cada línea
		int total_len = strlen(nombres[i]) + strlen(roles[i]) + 5; // +5 por " • " y " - "
		int espacios = (ANCHO_CONSOLA - total_len) / 2;
		
		// Imprimir espacios iniciales
		for(int j = 0; j < espacios; j++) printf(" ");
		
		// Efecto de escritura para nombre
		printf("• %s - ", nombres[i]);
		
		// Efecto de escritura para rol
		for(int j = 0; j < strlen(roles[i]); j++) {
			printf("%c", roles[i][j]);
			fflush(stdout);
			Sleep(100);
		}
		printf("\n");
	}
	
	printf("\n");
	// Centrar mensaje final
	int msg_len = strlen("Presione cualquier tecla para continuar...");
	int espacios_msg = (ANCHO_CONSOLA - msg_len) / 2;
	for(int i = 0; i < espacios_msg; i++) printf(" ");
	printf("Presione cualquier tecla para continuar...");
	
	getch();
}
