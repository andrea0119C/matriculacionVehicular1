//Librer�as est�ndar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>

//Librer�a propia
#include "registroVehiculos.h"
#include "ingreso.h"
#include "bloqueo.h"
#include "creditos.h"

#define Max_intentos 3
#define Max_len 30

//Funci�n para limpiar la pantalla
void limpiarPantalla(){
	system("cls");
}
	
void limpiarBuffer() {
		int c;
		while ((c = getchar()) != '\n' && c != EOF) {}
	}
	
//Funci�n para continuar al presionar Enter
void pausa(){
	printf("\nPresione ENTER para continuar...");
	while (getchar() !='\n');
}
	
//Funci�n principal
int main(){
	
	setlocale(LC_ALL, "");
	int contador=0;
	int opcion;
	int salir=0;
	vehiculo vehiculos[2000];
	
	char usuario[MAX_USUARIO];
	printf("Usuario: ");
	scanf("%s", usuario);
	limpiarBuffer();
	
	
	while (strlen(usuario) < 8) {
		printf("El nombre de usuario debe tener al menos 8 caracteres.\n Intente nuevamente: ");
		scanf("%s", usuario);
		limpiarBuffer();
	}
	char clave[MAX_CLAVE];
	int resultado;
	
	int intentos = 0;
	while (intentos < MAX_INTENTOS) {
		printf("Clave: ");
		leerContrasena(clave, MAX_CLAVE);
		
		resultado = autenticar(usuario, clave);
		
		if (resultado == 1) {
			printf("Autenticaci�n exitosa. Bienvenido, %s.\n", usuario);
			pausa();
			break;
		} else if (resultado == 0) {
			limpiarPantalla();
			printf("Clave incorrecta. Intento %d de %d.\n", ++intentos, MAX_INTENTOS);
		} else if (resultado == 2) {
			int opcionRegistro = -1;
			char linea[10];
			do {
				printf("Usuario no encontrado.\n");
				printf("�Deseas registrarte como '%s'? (1 = S�, 0 = No): ", usuario);

				if (fgets(linea, sizeof(linea), stdin) == NULL) {
					printf("Error leyendo entrada.\n");
					return 1;
				}
				// Quitar salto de l�nea
				linea[strcspn(linea, "\n")] = 0;
				
				// Validar que sea s�lo '0' o '1'
				if (strlen(linea) == 1 && (linea[0] == '0' || linea[0] == '1')) {
					opcionRegistro = linea[0] - '0';
				} else {
					printf("Opci�n inv�lida. Intente de nuevo.\n");
				}
			} while (opcionRegistro == -1);
			
			if (opcionRegistro == 1) {
				printf("Elige una clave: ");
				scanf("%s", clave);
				limpiarBuffer();
				if (registrarUsuario(usuario, clave)) {
					printf("Usuario registrado exitosamente.\n");
				} else {
					printf("Error al registrar usuario.\n");
				}
				pausa();
				break;
			} else {
				printf("No se registr� el usuario. Saliendo del programa.\n");
				return 0; // Termina el programa inmediatamente
			}
		} else {
			printf("Error general.\n");
			return 1;
		}
	}
	if (intentos == MAX_INTENTOS) {
		printf("Demasiados intentos fallidos. Acceso bloqueado.\n");
		return 1;
	}
	

	do{
		limpiarPantalla();
		
		printf("+--------------------------------------------------------------+\n");
		printf("�        Sistema Integral de Matriculaci�n Vehicular           �\n");
		printf("�                        POLIDRIVE�                            �\n");
		printf("�--------------------------------------------------------------�\n");
		printf("�  1. Registrar el veh�culo                                    �\n");
		printf("�  2. Registrar cumplimiento de revisiones t�cnicas            �\n");
		printf("�  3. Buscar veh�culo por placa                                �\n");
		printf("�  4. Lista de veh�culos matriculados                          �\n");
		printf("�  5. Cr�ditos                                                 �\n");
		printf("�  6. Salir                                                    �\n");
		printf("+--------------------------------------------------------------+\n");
		printf("Seleccione una opci�n: ");
		
		if(scanf("%d",&opcion) != 1){
			printf("Entrada no v�lida\n");
			while (getchar() != '\n');
			pausa();
			continue;
		}
			while (getchar() != '\n');
			
		switch(opcion){
		case 1:
				
			limpiarPantalla();
			if(contador < 2000)
			{
				printf("\t Registro de Vehiculo #%d \n", contador + 1);
				registroVehiculo(&vehiculos[contador], vehiculos, contador);
				contador++;
				pausa();
			}else{
				printf("No se puede registrar m�s veh�culos.\n");
				pausa();
			}
			realizadoOpcion1 = 1;
			break;
			
		case 2: 
			if(!validarOpcion2()) break;
			limpiarPantalla();
			registrarRevisionTecnica(vehiculos, contador);
			while (getchar() != '\n');			
			pausa();
			realizadoOpcion2 = 1;
			break;
			
		case 3:
			if(!validarOpcion3()) break;
			limpiarPantalla();
			buscarPorPlaca(vehiculos, contador);
			pausa();
			realizadoOpcion3 = 1;
			break;
			
		case 4:
			if(!validarOpcion4()) break;
			limpiarPantalla();
			listarVehiculos(vehiculos, contador);
			pausa();
			break;
			
		case 5:
			limpiarPantalla();
			mostrarCreditos();
			break;
			
	    case 6:
			printf("Saliendo del programa\n");
			salir=1;
			break;
	default:
		printf("Opci�n no valida. Intentar de nuevo\n");
		pausa();
		break;
	    }
		
    }while (salir==0);
	
	return 0;
}
