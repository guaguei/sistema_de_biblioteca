#include "biblioteca.h" // Incluye la cabecera con definiciones y prototipos
#include <stdio.h>      // Para entrada/salida (printf, scanf, fopen, fclose, etc.)
#include <stdlib.h>     // Para funciones generales (qsort)
#include <string.h>     // Para manipulación de cadenas (strcpy, strcmp, strstr, strcspn)

// --- Variables Globales (Privadas a biblioteca.c, pero usadas por sus funciones) ---
// Se declaran aquí porque son parte del estado interno de la implementación de la biblioteca
Libro biblioteca[MAX_LIBROS];
int num_libros = 0; // Contador de libros actualmente en la biblioteca

// --- Funciones Auxiliares (no se exponen en el .h) ---
static void limpiar_buffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

// Función de comparación para qsort (ordenar por título)
static int comparar_por_titulo(const void *a, const void *b) {
	Libro *libroA = (Libro *)a;
	Libro *libroB = (Libro *)b;
	return strcmp(libroA->titulo, libroB->titulo);
}

// Función de comparación para qsort (ordenar por autor)
static int comparar_por_autor(const void *a, const void *b) {
	Libro *libroA = (Libro *)a;
	Libro *libroB = (Libro *)b;
	return strcmp(libroA->autor, libroB->autor);
}

// --- Implementación de Funciones Públicas (desde biblioteca.h) ---

// Función para inicializar el sistema (cargar datos al inicio)
void inicializar_sistema() {
	cargar_datos();
}

void registrar_libro() {
	if (num_libros >= MAX_LIBROS) {
		printf("ERROR: La biblioteca esta llena. No se pueden agregar mas libros.\n");
		return;
	}
	
	printf("\n--- Registrar Nuevo Libro ---\n");
	printf("Titulo: ");
	fgets(biblioteca[num_libros].titulo, MAX_STR, stdin);
	biblioteca[num_libros].titulo[strcspn(biblioteca[num_libros].titulo, "\n")] = 0; // Eliminar el salto de linea
	
	printf("Autor: ");
	fgets(biblioteca[num_libros].autor, MAX_STR, stdin);
	biblioteca[num_libros].autor[strcspn(biblioteca[num_libros].autor, "\n")] = 0; // Eliminar el salto de linea
	
	printf("Codigo (unico): ");
	fgets(biblioteca[num_libros].codigo, MAX_STR, stdin);
	biblioteca[num_libros].codigo[strcspn(biblioteca[num_libros].codigo, "\n")] = 0; // Eliminar el salto de linea
	
	biblioteca[num_libros].estado = 0; // 0 = Disponible por defecto
	
	num_libros++;
	printf("Libro registrado exitosamente.\n");
}

void prestar_devolver_libro(int es_prestamo) {
	char codigo_buscar[MAX_STR];
	int encontrado = 0;
	
	printf("\n--- %s Libro ---\n", es_prestamo ? "Prestar" : "Devolver");
	printf("Ingrese el codigo del libro: ");
	fgets(codigo_buscar, MAX_STR, stdin);
	codigo_buscar[strcspn(codigo_buscar, "\n")] = 0;
	
	for (int i = 0; i < num_libros; i++) {
		if (strcmp(biblioteca[i].codigo, codigo_buscar) == 0) {
			if (es_prestamo) {
				if (biblioteca[i].estado == 0) { // Si esta disponible
					biblioteca[i].estado = 1; // Marcar como prestado
					printf("Libro '%s' (Codigo: %s) prestado exitosamente.\n", biblioteca[i].titulo, biblioteca[i].codigo);
				} else {
					printf("El libro '%s' ya se encuentra prestado.\n", biblioteca[i].titulo);
				}
			} else { // Es devolver
				if (biblioteca[i].estado == 1) { // Si esta prestado
					biblioteca[i].estado = 0; // Marcar como disponible
					printf("Libro '%s' (Codigo: %s) devuelto exitosamente.\n", biblioteca[i].titulo, biblioteca[i].codigo);
				} else {
					printf("El libro '%s' ya se encuentra disponible.\n", biblioteca[i].titulo);
				}
			}
			encontrado = 1;
			break;
		}
	}
	
	if (!encontrado) {
		printf("Libro con codigo '%s' no encontrado.\n", codigo_buscar);
	}
}

void buscar_libro() {
	char termino_busqueda[MAX_STR];
	int encontrado = 0;
	
	printf("\n--- Buscar Libro ---\n");
	printf("Ingrese el titulo o autor a buscar: ");
	fgets(termino_busqueda, MAX_STR, stdin);
	termino_busqueda[strcspn(termino_busqueda, "\n")] = 0;
	
	printf("\nResultados de la busqueda:\n");
	for (int i = 0; i < num_libros; i++) {
		if (strstr(biblioteca[i].titulo, termino_busqueda) != NULL ||
			strstr(biblioteca[i].autor, termino_busqueda) != NULL) {
			printf("  Titulo: %s, Autor: %s, Codigo: %s, Estado: %s\n",
				   biblioteca[i].titulo, biblioteca[i].autor, biblioteca[i].codigo,
				   biblioteca[i].estado == 0 ? "Disponible" : "Prestado");
			encontrado = 1;
		}
	}
	
	if (!encontrado) {
		printf("No se encontraron libros que coincidan con '%s'.\n", termino_busqueda);
	}
}

void listar_libros() {
	if (num_libros == 0) {
		printf("No hay libros registrados en la biblioteca.\n");
		return;
	}
	
	int opcion_orden;
	printf("\n--- Listar Libros ---\n");
	printf("Ordenar por:\n");
	printf("1. Titulo\n");
	printf("2. Autor\n");
	printf("Ingrese su opcion de ordenamiento: ");
	scanf("%d", &opcion_orden);
	limpiar_buffer(); // Limpiar el buffer después de leer un entero
	
	if (opcion_orden == 1) {
		qsort(biblioteca, num_libros, sizeof(Libro), comparar_por_titulo);
		printf("\nLibros listados por Titulo:\n");
	} else if (opcion_orden == 2) {
		qsort(biblioteca, num_libros, sizeof(Libro), comparar_por_autor);
		printf("\nLibros listados por Autor:\n");
	} else {
		printf("Opcion de ordenamiento invalida. Mostrando sin ordenar.\n");
	}
	
	for (int i = 0; i < num_libros; i++) {
		printf("  Titulo: %s\n", biblioteca[i].titulo);
		printf("  Autor: %s\n", biblioteca[i].autor);
		printf("  Codigo: %s\n", biblioteca[i].codigo);
		printf("  Estado: %s\n", biblioteca[i].estado == 0 ? "Disponible" : "Prestado");
		printf("--------------------\n");
	}
}

void guardar_datos() {
	FILE *fp = fopen(FILENAME, "w"); // Abrir en modo escritura (sobrescribe si existe)
	if (fp == NULL) {
		printf("ERROR: No se pudo abrir el archivo para guardar datos.\n");
		return;
	}
	
	fprintf(fp, "%d\n", num_libros); // Guardar el número de libros primero
	for (int i = 0; i < num_libros; i++) {
		fprintf(fp, "%s\n%s\n%s\n%d\n",
				biblioteca[i].titulo,
				biblioteca[i].autor,
				biblioteca[i].codigo,
				biblioteca[i].estado);
	}
	
	fclose(fp);
	printf("Datos guardados exitosamente en %s.\n", FILENAME);
}

void cargar_datos() {
	FILE *fp = fopen(FILENAME, "r"); // Abrir en modo lectura
	if (fp == NULL) {
		printf("Advertencia: No se encontraron datos previos (%s). Iniciando con biblioteca vacia.\n", FILENAME);
		num_libros = 0; // Asegurarse de que el contador de libros esté a 0
		return;
	}
	
	fscanf(fp, "%d\n", &num_libros); // Leer el número de libros
	for (int i = 0; i < num_libros; i++) {
		// Usar fgets para leer cadenas y luego eliminar el salto de línea
		fgets(biblioteca[i].titulo, MAX_STR, fp);
		biblioteca[i].titulo[strcspn(biblioteca[i].titulo, "\n")] = 0;
		
		fgets(biblioteca[i].autor, MAX_STR, fp);
		biblioteca[i].autor[strcspn(biblioteca[i].autor, "\n")] = 0;
		
		fgets(biblioteca[i].codigo, MAX_STR, fp);
		biblioteca[i].codigo[strcspn(biblioteca[i].codigo, "\n")] = 0;
		
		fscanf(fp, "%d\n", &biblioteca[i].estado);
	}
	
	fclose(fp);
	printf("Datos cargados exitosamente desde %s.\n", FILENAME);
}

void gestionar_prestamos_activos() {
	int encontrados = 0;
	printf("\n--- Prestamos Activos ---\n");
	for (int i = 0; i < num_libros; i++) {
		if (biblioteca[i].estado == 1) { // Si el libro está prestado
			printf("  Titulo: %s, Autor: %s, Codigo: %s\n",
				   biblioteca[i].titulo, biblioteca[i].autor, biblioteca[i].codigo);
			encontrados = 1;
		}
	}
	if (!encontrados) {
		printf("No hay prestamos activos en este momento.\n");
	}
}
