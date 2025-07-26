//Librería de registro
#ifndef registroVehiculos_h
#define registroVehiculos_h

// Estructura
typedef struct {
	char placa[8];
	char cedula[11];
	int anio;
	int tipo;
	int subtipo;
	int cilindraje;
	float avaluo;
	float matricula;
	int esEcologico;
	int pagoConAnticipo;
	int pasoRevisionTecnica;
	int pagoATiempo;
	int multaPorEstadoEtilico;
	int multaPorSinCinturon;
	int multaPorSobrepasarLimiteDeVelocidad;
	int opcion;
	int revision1, revision2, revisionActual;
	int revisionRegistrada;
	int revisionesAprobadas;
	// Campos ampliados para revisiones
	struct {
		int puntaje;
		char fecha[11]; // Formato DD-MM-AAAA
		float descuentoAplicado; // % de descuento obtenido
		int aprobada; // 1 si aprobó, 0 si no
	} revisionAnterior[2]; // Para las 2 revisiones anteriores
	float descuentoPorHistorial; // Descuento acumulado por buen historial
} vehiculo;

// Funciones principales
void limpiarPantalla();
void registroVehiculo(vehiculo *veh, vehiculo *vehiculos, int total);
float calcularAvaluo(vehiculo v);
float calcularValorMatricula(vehiculo v);
void mostrarHistorialRevisiones(vehiculo v);
int evaluarRevisionTecnica(vehiculo *v);
void registrarRevisionTecnica(vehiculo *vehiculos, int total);
void buscarPorPlaca(vehiculo *vehiculos, int total);
void listarVehiculos(vehiculo *vehiculos, int total);


// Funciones auxiliares (declaraciones)
int validarCedula(const char *ced);
int validarTipo(int tipo);
int validarAnio(int anio);
int validarSubtipo(int tipo, int subtipo);
void mostrarSubtipoYCilindraje(int tipo, int subtipo);
int validarDescuento(int opcion);
int validarRetencion(int opcion);
int validarMultas (int opcion);
int leerPuntaje(const char *mensaje, int min, int max);
const char* obtenerFechaActual();
//Fin de libreria propia
#endif
	
