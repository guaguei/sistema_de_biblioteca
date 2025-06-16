#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

// --- Constantes ---
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

// --- Estructura para un Nodo de la Lista Enlazada ---
typedef struct NodoLibro {
	Libro datos;
	struct NodoLibro *siguiente;
} NodoLibro;

// --- Prototipos de Funciones ---
// Funciones principales del sistema de biblioteca
void inicializar_sistema(); // Carga los datos al inicio y inicializa la lista
void registrar_libro();
void prestar_devolver_libro(int es_prestamo); // 1 para prestar, 0 para devolver
void buscar_libro();
void listar_libros();
void guardar_datos(); // Guarda los datos de la lista enlazada
void gestionar_prestamos_activos();
void liberar_memoria(); // Libera la memoria de la lista enlazada al salir

#endif // BIBLIOTECA_H
