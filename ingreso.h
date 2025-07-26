//Librería de ingreso
#ifndef ingreso_h
#define ingreso_h

//Definir valores constantes
#define MAX_LINEA 100
#define MAX_USUARIO 50
#define MAX_CLAVE 50
#define MAX_INTENTOS 3

// Prototipos de funciones
void limpiarPantalla();
void leerContrasena(char *buffer, int max_len);
int autenticar(const char *usuario, const char *clave);
int registrarUsuario(const char *usuario, const char *clave);

#endif
