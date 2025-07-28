//Libreráas estándar
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>



//Librería propia
#include "registroVehiculos.h"

//Función para mayúsculas 
void strToLower(char *str){
	for(int i=0; str[i]; i++){
		if (str[i] >= 'A' && str[i] <= 'Z'){
			str[i] += 'a' - 'A';
		}
	}
}
	
//Función auxiliar para validar cédula
int validarCedula(const char *ced){
	if(strlen(ced) != 10)
		return 0;
	for(int i = 0; i < 10; i++){
		if(!isdigit(ced[i]))
			return 0;
	}
	return 1;
}

//Función auxiliar para validar el año	
int validarAnio(int anio) {
	return (anio >= 2000 && anio <= 2025);
}

//Función auxiliar para validar tipo
int validarTipo(int tipo){
	return( tipo == 0 || tipo == 1 || tipo == 2 || tipo == 3);
}

//Función auxiliar para mostrar en texto el tipo
const char* tipoTexto(int tipo){
	switch(tipo){
		case 0: return "Moto";
		case 1: return "Liviano";
		case 2: return "Mediano";
	    case 3: return "Pesado";
		default: return "Desconocido";
	}
}

//Función auxiliar para validar Subtipo dependiendo el tipo
int validarSubtipo(int tipo, int subtipo){
	switch(tipo){
	case 0: return(subtipo >= 0 && subtipo <=1);
	case 1: return(subtipo >= 0 && subtipo <=1);
	case 2: return(subtipo >= 0 && subtipo <=1);
	case 3: return(subtipo >= 0 && subtipo <=1);
	default: return 0;
	}
}

//Mostrar cilindraje
void mostrarSubtipoYCilindraje(int tipo, int subtipo){
int cilindraje [4][2] ={
	{100, 200},
	{1200, 2000},
	{2500, 3000},
	{4000, 5000,}
};
printf("Subtipo: %d \nCilindraje: %dcc\n", subtipo, cilindraje[tipo][subtipo]);
}

//Función auxiliar para validar descuento
int validarDescuento(int opcion){
	return ( opcion == 0 || opcion == 1);
}

//Función auxiliar para validar retención
int validarRetencion(int opcion){
	return ( opcion == 0 || opcion == 1);
}

//Función auxiliar para validar multas
int validarMultas(int opcion){
	return (opcion >= 0 && opcion <= 3);
}

//Función validar valores enteros
int leerEnteroLimpio(const char *entrada, int *valor) {
	char temp;
	if (sscanf(entrada, "%d %c", valor, &temp) != 1)
		return 0;
	
	char limpio[10];
	strncpy(limpio, entrada, sizeof(limpio));
	limpio[strcspn(limpio, "\n")] = '\0';
	
	for (int i = 0; limpio[i] != '\0'; i++) {
		if (!isdigit(limpio[i]))//Esta parte asegura que sea un número sin ningún caracter
			return 0;
	}
	
	if (strlen(limpio) > 1 && limpio[0] == '0')
		return 0;
	
	return 1;
}

//Función para limpiar el buffer
void limpiarBufferExtra(char *entrada) {
	if (!strchr(entrada, '\n')) {
		int c;
		while ((c = getchar()) != '\n' && c != EOF); // Limpiar entrada sobrante
	}
}

//Función para registrar los vehículos
void registroVehiculo(vehiculo *veh, vehiculo *vehiculos, int total){
	char buffer[100];
	int valida=0;
	int tipoValido;
	char entrada[10];
	
	while(!valida){
		
	 
	printf("Ingrese la placa del vehículo (Ejemplo:PHE1234): \n");
	//Ingrese la placa del vehículo
	scanf("%s", veh->placa);
	fflush(stdin);
	
	if(strlen(veh->placa)==7){
		int letras = 1, numeros=1;
		
		for(int i=0; i < 3; i++){
			if(!isalpha(veh->placa[i])){
				letras=0;
				break;
			}
		}
		for (int i=3; i<7; i++){
			if(!isdigit(veh->placa[i])){
				numeros =0;
				break;
			}
		}
		// Verificar si ya existe la placa en vehiculos
		int placaRepetida = 0;
		for (int i = 0; i < total; i++) {
			if (strcasecmp(vehiculos[i].placa, veh->placa) == 0) {
				placaRepetida = 1;
				break;
			}
		}
		
		if(placaRepetida){
			printf("Este vehículo ya fue registrado.\n");
		}
		else if(letras && numeros){
			valida = 1;
		}
		else{
			limpiarPantalla();
			printf("Placa inválida. Intente nuevamente.\n");
		}
	}
	else{
		limpiarPantalla();
		printf("La placa debe tener exactamente 7 caracteres.\n");
	}
	}
	memset(&veh->revisionAnterior, 0, sizeof(veh->revisionAnterior));
	veh->revisionRegistrada = 0;
	veh->revisionActual = 0;
	veh->revision1 = 0;
	veh->revision2 = 0;
	veh->descuentoPorHistorial = 0.0f;
	limpiarPantalla();
		
		//Ingrese el número de cédula del usuario
	do {
		printf("Ingrese la cédula del usuario (10 dígitos): \n");
		fgets(buffer, sizeof(buffer), stdin);
		buffer[strcspn(buffer, "\n")] = '\0'; // Quita salto de línea
		
		if (validarCedula(buffer)) {
			strncpy(veh->cedula, buffer, sizeof(veh->cedula));
			break;
		} else {
			limpiarPantalla();
			printf("Cédula inválida. Debe tener exactamente 10 dígitos numéricos.\n");
		}
	} while (1);
	limpiarPantalla();
		
	//Ingrese el año del vehículo
	do {
		printf("Ingrese el año del vehículo: \n");
		fgets(buffer, sizeof(buffer), stdin);
		buffer[strcspn(buffer, "\n")] = '\0';
		
		// Verificamos que sea un número
		int esNumero = 1;
		for (int i = 0; buffer[i] != '\0'; i++) {
			if (!isdigit(buffer[i])) {
				esNumero = 0;
				break;
			}
		}
		
		if (esNumero) {
			int anioIngresado = atoi(buffer);
			if (validarAnio(anioIngresado)) {
				veh->anio = anioIngresado;
				break;
			}
		}
		limpiarPantalla();
		printf("Año inválido. Debe estar entre 2000 y 2025.\n");
	} while (1);
	limpiarPantalla();	
	//Ingrese el tipo de vehículo
	do {
		printf("Ingrese el tipo de vehículo \n 0.-Moto \n 1.-Liviano \n 2.-Mediano \n 3.-Pesado: \n");
		fgets(entrada, sizeof(entrada), stdin);
		limpiarBufferExtra(entrada);
		tipoValido = leerEnteroLimpio(entrada, &veh->tipo);
		
		if (tipoValido == 1 && validarTipo(veh->tipo)) {
			break; // válido
		} else {
			limpiarPantalla();  // ? Limpia pantalla
			printf("Tipo inválido. Solo se permite: 0, 1, 2 o 3.\n\n");
		}
	} while (1);
	limpiarPantalla();
	//Ingrese el subtipo
	int subtipoIngresado;
	do{
		printf("Ingrese el Cilindraje de vehículo para el tipo %s:\n", tipoTexto(veh->tipo));
		switch(veh->tipo){
		case 0:
			printf(" 0.- 100cc\n 1.-200cc\n");
			break;
		case 1:
			printf(" 0.- 1200cc\n 1.-2000cc\n");
			break;
		case 2:
			printf(" 0.- 2500cc\n 1.- 3000cc\n");
			break;
		case 3:
			printf(" 0.- 4000cc\n 1.-5000cc\n");
			break;
		}
	 fgets(entrada, sizeof(entrada), stdin);
		limpiarBufferExtra(entrada);
		tipoValido = leerEnteroLimpio(entrada, &subtipoIngresado);
		if (tipoValido == 1 && validarSubtipo(veh->tipo, subtipoIngresado)) {
			break;
		} else {
			limpiarPantalla();
			printf("Opción inválida. Ingrese 0 o 1.\n\n");
		}
	} while (1);
	veh->subtipo = subtipoIngresado;
	
	int cilindraje[4][2] ={
		{100, 200},
	    {1200, 2000},
		{2500, 3000},
		{4000, 5000},
	};
	veh->cilindraje= cilindraje [veh->tipo][veh->subtipo];
	limpiarPantalla();
	
	//Descuento para auto ecológico
	do{
	    printf("El vehículo es ecológico: \n Ingrese:\n 0.- Si es ecológico \n 1.- No es ecológico:\n");
		fgets(entrada, sizeof(entrada), stdin);
		limpiarBufferExtra(entrada);
		tipoValido = leerEnteroLimpio(entrada, &veh->esEcologico);
	    
		if (tipoValido == 1 && validarDescuento(veh->esEcologico)) {
			break;
		} else {
			limpiarPantalla();
			printf("Opción inválida. Solo se permite ingresar 0 o 1.\n\n");
		}
	} while (1);
	limpiarPantalla();
	
	//Descuento por pago anticipado
	do{
	    printf("Realizo el usuario el pago antes de tiempo: \n Ingrese: \n 0.- Si es correcto \n 1.- No es correcto: \n");
		fgets(entrada, sizeof(entrada), stdin);
		limpiarBufferExtra(entrada);
		tipoValido = leerEnteroLimpio(entrada, &veh->pagoConAnticipo);
		if (tipoValido == 1 && validarDescuento(veh->pagoConAnticipo)) {
			break;
		} else {
			limpiarPantalla();
			printf("Opción inválida. Solo se permite ingresar 0 o 1.\n\n");
		}
	} while (1);
	limpiarPantalla();
	
	//Retención si el pago se hizo a tiempo
	do{
	    printf("El usuario realizo el pago a tiempo: \n Ingrese: \n 0.- Si es correcto \n 1.- No es correcto:\n");
		fgets(entrada, sizeof(entrada), stdin);
		limpiarBufferExtra(entrada);
		tipoValido = leerEnteroLimpio(entrada, &veh->pagoATiempo);
		if (tipoValido == 1 && validarRetencion(veh->pagoATiempo)) {
			break;
		} else {
			limpiarPantalla();
			printf("Opción inválida. Solo se permite ingresar 0 o 1.\n\n");
		}
	} while (1);
	limpiarPantalla();
	
	// MULTA POR ESTADO ETÍLICO
	do {
		printf("El usuario tiene multas por manejar en estado etílico:\n");
		printf("0.- Sin multas\n1.- Leve \n2.- Moderada \n3.- Grave\n");
		fgets(entrada, sizeof(entrada), stdin);
		limpiarBufferExtra(entrada);
		tipoValido = leerEnteroLimpio(entrada, &veh->multaPorEstadoEtilico);
		if (tipoValido == 1 && validarMultas(veh->multaPorEstadoEtilico)) {
			break;
		} else {
			limpiarPantalla();
			printf("Opción inválida. Solo se permite ingresar 0 a 3.\n\n");
		}
	} while (1);
	limpiarPantalla();
	
	int mostrarError = 0;
	// MULTA POR NO USAR CINTURÓN O CASCO
	do {
		limpiarPantalla();
		
		if (mostrarError) {
			printf("Opción inválida. Solo se permite ingresar un número del 0 al 3.\n\n");
			mostrarError = 0; // Ya mostramos el error, lo reseteamos
		}
		
		if (veh->tipo == 0) {
			printf("Multa por no usar casco:\n");
			printf("0.- Sin multa\n1.- Casco no abrochado\n2.- Casco inadecuado\n3.- Sin casco\n");
		} else {
			printf("Multa por no usar cinturón de seguridad:\n");
			printf("0.- Sin multa\n1.- Un cinturón\n2.- Dos o tres cinturones\n3.- Cuatro o cinco cinturones\n");
		}
		
		fgets(entrada, sizeof(entrada), stdin);
		limpiarBufferExtra(entrada);
		tipoValido = leerEnteroLimpio(entrada, &veh->multaPorSinCinturon);
		
		if (!(tipoValido && validarMultas(veh->multaPorSinCinturon))) {
			mostrarError = 1;  // Indicamos que hay error para mostrarlo en la próxima iteración
		}
		
	} while (!(tipoValido && validarMultas(veh->multaPorSinCinturon)));
	
	limpiarPantalla();
	
	// MULTA POR EXCESO DE VELOCIDAD
	do {
		printf("El usuario tiene multas por sobrepasar el límite de velocidad:\n");
		printf("0.- Sin multas\n1.- Leve \n2.- Moderada\n3.- Grave\n");
		fgets(entrada, sizeof(entrada), stdin);
		limpiarBufferExtra(entrada);
		tipoValido = leerEnteroLimpio(entrada, &veh->multaPorSobrepasarLimiteDeVelocidad);
		if (tipoValido == 1 && validarMultas(veh->multaPorSobrepasarLimiteDeVelocidad)) {
			break;
		} else {
			limpiarPantalla();
			printf("Opción inválida. Solo se permite ingresar 0 a 3.\n\n");
		}
	} while (1);
	limpiarPantalla();
	
	veh->avaluo = calcularAvaluo(*veh);
   }
//Función principal para calcular Avaluo
float calcularAvaluo(vehiculo v){
	float base=0.0f;
	float depreciacion_anual = 0.0f;
	
	if(v.tipo == 0){
		base=2000;
		depreciacion_anual=0.08f;
	}else if(v.tipo == 1){
		base=15000;
		depreciacion_anual=0.10f;
	}else if (v.tipo == 2){
		base=25000;
		depreciacion_anual=0.12f;
	}else if (v.tipo == 3){
		base=40000;
		depreciacion_anual=0.15f;
	}else {
		base=10000;
		depreciacion_anual=0.10f;
	}
	
	if (v.cilindraje > 1000){
		base+= (v.cilindraje -1000)*10;
	}
	
	int antiguedad=2025-v.anio;
	float depreciacion=antiguedad * depreciacion_anual;
	float factor=1.0f - depreciacion;
	
	if(factor<0.3f){
		factor=0.3f;
	}
	return base*factor;
}
	
	// Función para obtener la fecha actual
	const char* obtenerFechaActual() {
		static char fecha[11]; // Formato: DD-MM-AAAA
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		sprintf(fecha, "%02d-%02d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
		return fecha;
	}
	
	// Función auxiliar para verificar entradas
	int leerEnteroValido(const char *mensaje, int min, int max) {
		char buffer[100];
		int valor;
		int valido = 0;
		
		do {
			printf("%s (%d-%d): ", mensaje, min, max);
			if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
				printf("Error al leer la entrada.\n");
				continue;
			}
			
			// Verificar si la entrada es solo un número sin caracteres adicionales
			size_t len = strlen(buffer);
			if (len > 0 && buffer[len-1] == '\n') {
				buffer[len-1] = '\0'; // Eliminar el salto de línea
				len--;
			}
			
			valido = 1;
			if (len == 0) {
				valido = 0;
			} else {
				for (size_t i = 0; i < len; i++) {
					if (!isdigit(buffer[i])) {
						valido = 0;
						break;
					}
				}
			}
			
			if (!valido) {
				printf("Entrada inválida. Solo se permiten números enteros.\n");
				continue;
			}
			
			valor = atoi(buffer);
			if (valor < min || valor > max) {
				printf("El valor debe estar entre %d y %d.\n", min, max);
				valido = 0;
			}
		} while (!valido);
		
		return valor;
	}
	
	//Función para mostrar el historia de revisiones
	void mostrarHistorialRevisiones(vehiculo v) {
		printf("\n========== HISTORIAL DE REVISIONES ==========\n");
		
		// Primera revisión
		if (v.revision1 == 0) {
			printf("1. Primera revisión: NO COMPLETADA\n");
		} else if (v.revision1 < 70) {
			printf("1. Primera revisión: %d/100 - REPROBADA\n", v.revision1);
			printf("   ¡Debe aprobar esta revisión antes de continuar!\n");
		} else {
			printf("1. Primera revisión: %d/100 - APROBADA\n", v.revision1);
		}
		
		// Segunda revisión
		if (v.revision2 == 0) {
			printf("2. Segunda revisión: NO COMPLETADA\n");
		} else if (v.revision2 < 70) {
			printf("2. Segunda revisión: %d/100 - REPROBADA\n", v.revision2);
			printf("   ¡Debe aprobar esta revisión antes de continuar!\n");
		} else {
			printf("2. Segunda revisión: %d/100 - APROBADA\n", v.revision2);
		}
		
		// Revisión actual (si existe)
		if (v.revisionRegistrada) {
			printf("\nREVISIÓN ACTUAL: %d/100 - %s\n", 
				   v.revisionActual,
				   (v.revisionActual >= 70) ? "APROBADA" : "REPROBADA");
			
			if (v.revisionActual < 70) {
				printf("¡No puede registrar su vehículo hasta aprobar la revisión técnica!\n");
			}
		} else {
			printf("\nREVISIÓN ACTUAL: NO REALIZADA\n");
		}
		
		// Validación general
		if ((v.revision1 > 0 && v.revision1 < 70) || 
			(v.revision2 > 0 && v.revision2 < 70)) {
			printf("\n¡ATENCIÓN! Tiene revisiones reprobadas pendientes.\n");
			printf("Debe aprobar todas las revisiones anteriores para continuar.\n");
		} else if (v.revision1 == 0 || v.revision2 == 0) {
			printf("\n¡ATENCIÓN! Tiene revisiones pendientes por completar.\n");
			printf("\n----------------------------------\n");
			}
	}
	
	//Función para otorgar descuento por revisiones anteriores   
	void calcularBeneficiosPorHistorial(vehiculo *v) {
		v->descuentoPorHistorial = 0.0f;
		
		// Descuento por revisiones anteriores aprobadas
		int revisionesAprobadas = 0;
		for(int i = 0; i < 2; i++) {
			if(v->revisionAnterior[i].aprobada) {
				revisionesAprobadas++;
				
				// Descuento adicional por puntaje alto
				if(v->revisionAnterior[i].puntaje > 85) {
					v->descuentoPorHistorial += 2.0f; // 2% adicional por cada revisión con más de 85
				}
			}
		}
		
		// Descuento base por historial
		if(revisionesAprobadas == 2) {
			v->descuentoPorHistorial += 5.0f; // 5% por tener las 2 revisiones aprobadas
		} else if(revisionesAprobadas == 1) {
			v->descuentoPorHistorial += 2.0f; // 2% por tener 1 revisión aprobada
		}
		
		// Límite máximo de descuento
		if(v->descuentoPorHistorial > 10.0f) {
			v->descuentoPorHistorial = 10.0f;
		}
	}
	
	// Función para evaluar las revisiones técnicas
	int evaluarRevisionTecnica(vehiculo *v) {
		limpiarPantalla();
		
		// Validación de revisiones anteriores
		printf("======= VALIDACIÓN DE REVISIONES ANTERIORES =======\n\n");
		
		// Primera revisión anterior
		printf("¿Pasó la PRIMERA revisión técnica? (1 = sí, 0 = no): ");
		int pasada1 = leerEnteroValido("", 0, 1);
		
		int puntaje1 = 0;
		if (pasada1) {
			limpiarPantalla();
			puntaje1 = leerEnteroValido("Ingrese el puntaje obtenido en la primera revisión ", 0, 100);
			
			if (puntaje1 < 70) {
				limpiarPantalla();
				printf("¡ERROR! La primera revisión técnica está REPROBADA (puntaje: %d/100)\n", puntaje1);
				printf("No puede realizar la revisión actual sin aprobar las revisiones anteriores.\n");
				printf("Por favor complete satisfactoriamente sus revisiones anteriores primero.\n");
				system("pause"); // Para que el usuario vea el mensaje
				return 0;
			}
		} else {
			limpiarPantalla();
			printf("¡ATENCIÓN! No ha completado la primera revisión técnica.\n");
			printf("Debe realizar y aprobar todas las revisiones anteriores primero.\n");
			system("pause");
			return 0;
		}
		
		// Segunda revisión anterior
		limpiarPantalla();
		printf("¿Pasó la SEGUNDA revisión técnica? (1 = sí, 0 = no): ");
		int pasada2 = leerEnteroValido("", 0, 1);
		
		int puntaje2 = 0;
		if (pasada2) {
			limpiarPantalla();
			puntaje2 = leerEnteroValido("Ingrese el puntaje obtenido en la segunda revisión ", 0, 100);
			
			if (puntaje2 < 70) {
				limpiarPantalla();
				printf("¡ERROR! La segunda revisión técnica está REPROBADA (puntaje: %d/100)\n", puntaje2);
				printf("No puede realizar la revisión actual sin aprobar las revisiones anteriores.\n");
				printf("Por favor complete satisfactoriamente sus revisiones anteriores primero.\n");
				system("pause");
				return 0;
			}
		} else {
			limpiarPantalla();
			printf("¡ATENCIÓN! No ha completado la segunda revisión técnica.\n");
			printf("Debe realizar y aprobar todas las revisiones anteriores primero.\n");
			system("pause");
			return 0;
		}
		
		// Guardar los puntajes en la estructura
		v->revision1 = puntaje1;
		v->revision2 = puntaje2;
		
		// Registrar beneficios de revisiones anteriores 
		for(int i = 0; i < 2; i++) {
			if((i == 0 && pasada1) || (i == 1 && pasada2)) {
				
				v->revisionAnterior[i].puntaje = (i == 0) ? v->revision1 : v->revision2;
				v->revisionAnterior[i].aprobada = (v->revisionAnterior[i].puntaje >= 70);
				
				// Calcular descuento aplicado en esa revisión
				if(v->revisionAnterior[i].aprobada) {
					v->revisionAnterior[i].descuentoAplicado = (v->revisionAnterior[i].puntaje - 70) * 0.2f; // 0.2% por punto arriba de 70
					if(v->revisionAnterior[i].descuentoAplicado > 5.0f) {
						v->revisionAnterior[i].descuentoAplicado = 5.0f;
					}
				}
			}
		}
		
		// Evaluación técnica actual
		int puntajes[8];
		const char *categorias[8] = {
			"Frenos",
				"Luces",
				"Emisiones",
				"Neumáticos",
				"Espejos y parabrisas",
				"Cinturones/Casco",
				"Bocina y limpiaparabrisas",
				"Documentación al día"
		};
		int maxPuntajes[8] = {25, 15, 15, 10, 10, 10, 5, 10};
		
		printf("\nEvaluación técnica actual:\n");
		int puntajeTotal = 0;
		for (int i = 0; i < 8; i++) {
			// Cambiamos la pregunta si es moto (tipo 0) y es la categoría 5 (cinturón/casco)
			if (i == 5 && v->tipo == 0) {  
				limpiarPantalla();
				printf("Categoría: Casco (para motocicletas)\n");
				puntajes[i] = leerEnteroValido("Ingrese puntaje para Casco ", 0, 10);
			} else {
				limpiarPantalla();
				printf("Categoría: %s\n", categorias[i]);
				puntajes[i] = leerEnteroValido("Ingrese puntaje", 0, maxPuntajes[i]);
			}
			puntajeTotal += puntajes[i];
		}
		
		// Preguntar al final si desea comprobante
		int imprimir;
		printf("\n¿Desea imprimir el comprobante? (1 = Sí, 0 = No): ");
		do {
			if (scanf("%d", &imprimir) != 1 || (imprimir != 0 && imprimir != 1)) {
				printf("Entrada inválida. Ingrese 1 (sí) o 0 (no): ");
				while (getchar() != '\n');
			}
		} while (imprimir != 0 && imprimir != 1);
		v->revisionActual = puntajeTotal;
		
		if (!imprimir) {
			printf("No se generará el comprobante.\n");
			return (puntajeTotal >= 70);
			v->revisionActual = puntajeTotal;
		}
		// Calcular matrícula antes de imprimir
		v->matricula = calcularValorMatricula(*v);
		// Calcular beneficios por historial
		calcularBeneficiosPorHistorial(v);
		
		// Aplicar descuento al avalúo
		v->avaluo *= (1.0f - v->descuentoPorHistorial/100.0f);
		
		// Imprimir comprobante
		FILE *archivo = fopen("resultado_revision.txt", "w");
		if (!archivo) {
			printf("No se pudo crear el archivo de resultados.\n");
			
			return (puntajeTotal >= 70);
		}
		
		// Generar comprobante con formato
		fprintf(archivo, "============================================\n");
		fprintf(archivo, "      COMPROBANTE DE REVISIÓN TÉCNICA       \n");
		fprintf(archivo, "============================================\n");
		fprintf(archivo, "Placa: %s\n", v->placa);
		fprintf(archivo, "Fecha: %s\n", obtenerFechaActual());
		fprintf(archivo, "--------------------------------------------\n");
		fprintf(archivo, "Revisión anterior 1: %d/100\n", v->revision1);
		fprintf(archivo, "Revisión anterior 2: %d/100\n", v->revision2);
		fprintf(archivo, "--------------------------------------------\n");
		fprintf(archivo, "REVISIÓN ACTUAL:\n");
		for (int i = 0; i < 8; i++) {
			fprintf(archivo, "  - %-20s: %2d/%2d\n", categorias[i], puntajes[i], maxPuntajes[i]);
		}
		fprintf(archivo, "--------------------------------------------\n");
		fprintf(archivo, "PUNTAJE TOTAL: %d/100\n", puntajeTotal);
		fprintf(archivo, "RESULTADO: %s\n", (puntajeTotal >= 70) ? "APROBADO" : "REPROBADO");
		fprintf(archivo, "--------------------------------------------\n");
		fprintf(archivo, "AVALÚO: $%.2f\n", v->avaluo);
		fprintf(archivo, "VALOR DE MATRÍCULA: $%.2f\n", v->matricula);
		fprintf(archivo, "============================================\n");
		
		fclose(archivo);
		
		printf("\nRevisión técnica %s.\n", (puntajeTotal >= 70) ? "APROBADA" : "REPROBADA");
		printf("Los resultados se han guardado en 'resultado_revision.txt'.\n");
		system("notepad resultado_revision.txt");
		
		v->revisionActual = puntajeTotal;
		return (puntajeTotal >= 70);
	}	
	
	// Función para registrar por matrícula las revisiones técnicas
	void registrarRevisionTecnica(vehiculo *vehiculos, int total) {
		char placa[8];
		int encontrado = 0;
		
		printf("Ingrese la placa del vehículo para registrar revisión técnica: ");
		scanf("%7s", placa);
		while (getchar() != '\n');  // Limpiar buffer
		
		for (int i = 0; i < total; i++) {
			if (strcasecmp(vehiculos[i].placa, placa) == 0) {
				encontrado = 1;
				
				// Verificar si ya se registró la matrícula (revisión aprobada)
				if (vehiculos[i].revisionRegistrada) {
					printf("Esta placa ya fue registrada la matrícula.\n");
					return; // Salir para no permitir registro duplicado
				}
				
				printf("\nVehículo encontrado: %s\n", vehiculos[i].placa);
				int resultado = evaluarRevisionTecnica(&vehiculos[i]);
				
				if (resultado) {
					printf("El vehículo %s ha APROBADO la revisión técnica.\n", vehiculos[i].placa);
				} else {
					printf("El vehículo %s ha REPROBADO la revisión técnica.\n", vehiculos[i].placa);
				}
				
				vehiculos[i].revisionRegistrada = 1;
				break;
			}
		}
		
		if (!encontrado) {
			printf("Vehículo no encontrado.\n");
		}
	}
	
	//Función principal para buscar por placa
void buscarPorPlaca(vehiculo *vehiculos, int total){
	char placaBuscada[8];
	int encontrado = 0;
	
	printf("Ingrese la placa del vehículo a buscar: ");
	scanf("%s", placaBuscada);
	fflush(stdin);
	
	for(int i = 0; i < total; i++){
		if(strcasecmp(vehiculos[i].placa, placaBuscada) == 0){
			printf("\n==========Vehículo encontrado==========\n");
			printf("Cédula: %s\n", vehiculos[i].cedula);
			printf("Año: %d\n", vehiculos[i].anio);
			printf("Tipo: %s\n", tipoTexto(vehiculos[i].tipo));
			printf("Subtipo - Cilindraje: %dcc\n", vehiculos[i].cilindraje);
			printf("Avalúo: $%.2f\n", vehiculos[i].avaluo);
			
			// Mostrar estado de aprobación
			if(vehiculos[i].revisionRegistrada) {
				printf("Estado de revisión: %s\n", 
					   (vehiculos[i].revisionActual >= 70) ? "APROBADO" : "REPROBADO");
				printf("Puntaje de revisión: %d/100\n", vehiculos[i].revisionActual);
			} else {
				printf("Estado de revisión: PENDIENTE (no registrada)\n");
			}
			// Mostrar historial de revisiones
			mostrarHistorialRevisiones(vehiculos[i]);
			
			encontrado = 1;
			break;
		}
	}
	if(!encontrado){
		printf("No se encontró un vehículo con esa placa.\n");
	}
}
//Función principal Listar Vehículos
	void listarVehiculos(vehiculo *vehiculos, int total) {
		int contador = 0;
		
		for(int i = 0; i < total; i++){
			// Mostrar solo si aprobó la revisión técnica
			if (vehiculos[i].revisionRegistrada && vehiculos[i].revisionActual >= 70) {
				contador++;
				
		
		printf("\n=== LISTADO DE VEHÍCULOS ===\n");
		
			printf("\nVehículo #%d:\n", contador);
			printf("Placa: %s\n", vehiculos[i].placa);
			printf("Cédula: %s\n", vehiculos[i].cedula);
			printf("Año: %d\n", vehiculos[i].anio);
			printf("Tipo: %s\n", tipoTexto(vehiculos[i].tipo));
			printf("Subtipo-cilindraje: %dcc\n", vehiculos[i].cilindraje);
			printf("Avalúo: $%.2f\n", vehiculos[i].avaluo);
			printf("====================================================\n");
			
			// Mostrar historial de revisiones
			mostrarHistorialRevisiones(vehiculos[i]);
			}
		}
		
		if (contador == 0) {
			printf("No hay vehículos registrados.\n");
		}
	}

//Función principal Calcular valor de matrícula
float calcularValorMatricula(vehiculo v){
	float total=0.0f;
	switch (v.tipo) {
	case 0: 
		switch (v.subtipo) {
		case 0: total = 30.0f; break; 
		case 1: total = 50.0f; break; 
		case 2: total = 80.0f; break; 
		default: total = 50.0f; 
		}
		break;
		
	case 1: 
		switch (v.subtipo) {
		case 0: total = 100.0f; break; 
		case 1: total = 150.0f; break; 
		case 2: total = 200.0f; break; 
		default: total = 150.0f;
		}
		break;
		
	case 2: 
		switch (v.subtipo) {
		case 0: total = 300.0f; break; 
		case 1: total = 350.0f; break; 
		default: total = 300.0f;
		}
		break;
		
	case 3: 
		switch (v.subtipo) {
		case 0: total = 400.0f; break; 
		case 1: total = 450.0f; break; 
		default: total = 400.0f;
		}
		break;
		
	default:
		total = 100.0f; 
	}
	
	// Calcular antigüedad
	int antiguedad = 2025 - v.anio;
	if(antiguedad > 10){
		total *= 0.7f; 
	} else if (antiguedad >= 8) {
		total *= 0.8f; 
	} else if (antiguedad >= 4) {
		total *= 0.9f; 
	}
	
	if(v.esEcologico ==0){
		total -=30.0;
	}
	
	if(v.pagoConAnticipo == 0){
		total -=10.0;
	}
	
	if(v.pasoRevisionTecnica == 1){
		total += 50.0;
	}
	
	if(v.pagoATiempo == 1){
		total += 25.0;
	}
	
	// Multas con niveles
	int montosEstadoEtilico[] =     {0, 100, 200, 350};
	if (v.tipo == 0) {  // Si es moto
		int montosSinCasco[] = {0, 50, 100, 200};
		total += montosSinCasco[v.multaPorSinCinturon]; 
	} else {
		int montosSinCinturon[] = {0, 25, 50, 100};
		total += montosSinCinturon[v.multaPorSinCinturon];
	}
	int montosExcesoVelocidad[] =   {0, 100, 250, 500};
	total += montosEstadoEtilico[v.multaPorEstadoEtilico];
	total += montosExcesoVelocidad[v.multaPorSobrepasarLimiteDeVelocidad];
	
	return total;
}
