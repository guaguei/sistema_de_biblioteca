#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

// --- Constantes ---
#define MAX_LIBROS 100 // Número máximo de libros que puede almacenar el sistema
#define MAX_STR 100    // Longitud máxima para cadenas (títulos, autores, códigos)
#define FILENAME "libros.txt" // Nombre del archivo para guardar/cargar datos

// --- Estructura para representar un Libro ---
typedef struct {
	char titulo[MAX_STR];
	char autor[MAX_STR];
	char codigo[MAX_STR];
	// 0: Disponible, 1: Prestado
	int estado;
} Libro;

// --- Prototipos de Funciones ---
// Funciones principales del sistema de biblioteca
void registrar_libro();
void prestar_devolver_libro(int es_prestamo); // 1 para prestar, 0 para devolver
void buscar_libro();
void listar_libros();
void guardar_datos();
void cargar_datos();
void gestionar_prestamos_activos();

// Prototipo de la función de inicialización, si es necesario
void inicializar_sistema();

#endif // BIBLIOTECA_H
