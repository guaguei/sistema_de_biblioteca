#include "biblioteca.h" // Incluye la cabecera con definiciones y prototipos
#include <stdio.h>      // Para entrada/salida (printf, scanf, fopen, fclose, etc.)
#include <stdlib.h>     // Para funciones generales (malloc, free, qsort, exit)
#include <string.h>     // Para manipulación de cadenas (strcpy, strcmp, strstr, strcspn)

// --- Variable Global para la cabeza de la Lista Enlazada ---
static NodoLibro *lista_libros = NULL; // Puntero al primer nodo de la lista
static int num_libros_actual = 0; // Contador de libros para guardar/cargar y otras operaciones

// --- Prototipos de Funciones Auxiliares (privadas a este archivo) ---
// Es fundamental declarar estas funciones antes de que sean usadas.
static void limpiar_buffer();
static void agregar_libro_a_lista(Libro nuevo_libro);
static NodoLibro* buscar_nodo_por_codigo(const char *codigo);
static int comparar_por_titulo(const void *a, const void *b);
static int comparar_por_autor(const void *a, const void *b);
static void cargar_datos(); // <-- ¡Aquí está la solución para la advertencia!

// --- Implementación de Funciones Auxiliares ---
static void limpiar_buffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

static void agregar_libro_a_lista(Libro nuevo_libro) {
	NodoLibro *nuevo_nodo = (NodoLibro *)malloc(sizeof(NodoLibro));
	if (nuevo_nodo == NULL) {
		printf("ERROR: No hay suficiente memoria para agregar el libro.\n");
		exit(EXIT_FAILURE); // Salir si no se puede asignar memoria
	}
	
	nuevo_nodo->datos = nuevo_libro;
	nuevo_nodo->siguiente = NULL;
	
	if (lista_libros == NULL) { // Si la lista está vacía
		lista_libros = nuevo_nodo;
	} else { // Recorrer hasta el final y añadir
		NodoLibro *actual = lista_libros;
		while (actual->siguiente != NULL) {
			actual = actual->siguiente;
		}
		actual->siguiente = nuevo_nodo;
	}
	num_libros_actual++;
}

static NodoLibro* buscar_nodo_por_codigo(const char *codigo) {
	NodoLibro *actual = lista_libros;
	while (actual != NULL) {
		if (strcmp(actual->datos.codigo, codigo) == 0) {
			return actual;
		}
		actual = actual->siguiente;
	}
	return NULL; // No encontrado
}

static int comparar_por_titulo(const void *a, const void *b) {
	Libro *libroA = (Libro *)a;
	Libro *libroB = (Libro *)b;
	return strcmp(libroA->titulo, libroB->titulo);
}

static int comparar_por_autor(const void *a, const void *b) {
	Libro *libroA = (Libro *)a;
	Libro *libroB = (Libro *)b;
	return strcmp(libroA->autor, libroB->autor);
}


// --- Implementación de Funciones Públicas (desde biblioteca.h) ---

void inicializar_sistema() {
	cargar_datos(); // La llamada a cargar_datos() ahora está bien porque su prototipo está arriba
}

void registrar_libro() {
	// ... (resto de la función igual) ...
	Libro nuevo_libro;
	
	printf("\n--- Registrar Nuevo Libro ---\n");
	printf("Titulo: ");
	fgets(nuevo_libro.titulo, MAX_STR, stdin);
	nuevo_libro.titulo[strcspn(nuevo_libro.titulo, "\n")] = 0; // Eliminar el salto de linea
	
	printf("Autor: ");
	fgets(nuevo_libro.autor, MAX_STR, stdin);
	nuevo_libro.autor[strcspn(nuevo_libro.autor, "\n")] = 0; // Eliminar el salto de linea
	
	printf("Codigo (unico): ");
	fgets(nuevo_libro.codigo, MAX_STR, stdin);
	nuevo_libro.codigo[strcspn(nuevo_libro.codigo, "\n")] = 0; // Eliminar el salto de linea
	
	nuevo_libro.estado = 0; // 0 = Disponible por defecto
	
	agregar_libro_a_lista(nuevo_libro);
	printf("Libro registrado exitosamente.\n");
}

void prestar_devolver_libro(int es_prestamo) {
	// ... (resto de la función igual) ...
	char codigo_buscar[MAX_STR];
	NodoLibro *libro_encontrado;
	
	printf("\n--- %s Libro ---\n", es_prestamo ? "Prestar" : "Devolver");
	printf("Ingrese el codigo del libro: ");
	fgets(codigo_buscar, MAX_STR, stdin);
	codigo_buscar[strcspn(codigo_buscar, "\n")] = 0;
	
	libro_encontrado = buscar_nodo_por_codigo(codigo_buscar);
	
	if (libro_encontrado != NULL) {
		if (es_prestamo) {
			if (libro_encontrado->datos.estado == 0) { // Si esta disponible
				libro_encontrado->datos.estado = 1; // Marcar como prestado
				printf("Libro '%s' (Codigo: %s) prestado exitosamente.\n", libro_encontrado->datos.titulo, libro_encontrado->datos.codigo);
			} else {
				printf("El libro '%s' ya se encuentra prestado.\n", libro_encontrado->datos.titulo);
			}
		} else { // Es devolver
			if (libro_encontrado->datos.estado == 1) { // Si esta prestado
				libro_encontrado->datos.estado = 0; // Marcar como disponible
				printf("Libro '%s' (Codigo: %s) devuelto exitosamente.\n", libro_encontrado->datos.titulo, libro_encontrado->datos.codigo);
			} else {
				printf("El libro '%s' ya se encuentra disponible.\n", libro_encontrado->datos.titulo);
			}
		}
	} else {
		printf("Libro con codigo '%s' no encontrado.\n", codigo_buscar);
	}
}

void buscar_libro() {
	// ... (resto de la función igual) ...
	char termino_busqueda[MAX_STR];
	int encontrado = 0;
	NodoLibro *actual = lista_libros;
	
	printf("\n--- Buscar Libro ---\n");
	printf("Ingrese el titulo o autor a buscar: ");
	fgets(termino_busqueda, MAX_STR, stdin);
	termino_busqueda[strcspn(termino_busqueda, "\n")] = 0;
	
	printf("\nResultados de la busqueda:\n");
	while (actual != NULL) {
		if (strstr(actual->datos.titulo, termino_busqueda) != NULL ||
			strstr(actual->datos.autor, termino_busqueda) != NULL) {
			printf("  Titulo: %s, Autor: %s, Codigo: %s, Estado: %s\n",
				   actual->datos.titulo, actual->datos.autor, actual->datos.codigo,
				   actual->datos.estado == 0 ? "Disponible" : "Prestado");
			encontrado = 1;
		}
		actual = actual->siguiente;
	}
	
	if (!encontrado) {
		printf("No se encontraron libros que coincidan con '%s'.\n", termino_busqueda);
	}
}

void listar_libros() {
	// ... (resto de la función igual) ...
	if (lista_libros == NULL) {
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
	
	Libro *temp_array = (Libro *)malloc(num_libros_actual * sizeof(Libro));
	if (temp_array == NULL) {
		printf("ERROR: No hay suficiente memoria para ordenar los libros.\n");
		return;
	}
	
	NodoLibro *actual = lista_libros;
	for (int i = 0; i < num_libros_actual; i++) {
		temp_array[i] = actual->datos;
		actual = actual->siguiente;
	}
	
	if (opcion_orden == 1) {
		qsort(temp_array, num_libros_actual, sizeof(Libro), comparar_por_titulo);
		printf("\nLibros listados por Titulo:\n");
	} else if (opcion_orden == 2) {
		qsort(temp_array, num_libros_actual, sizeof(Libro), comparar_por_autor);
		printf("\nLibros listados por Autor:\n");
	} else {
		printf("Opcion de ordenamiento invalida. Mostrando sin ordenar.\n");
	}
	
	for (int i = 0; i < num_libros_actual; i++) {
		printf("  Titulo: %s\n", temp_array[i].titulo);
		printf("  Autor: %s\n", temp_array[i].autor);
		printf("  Codigo: %s\n", temp_array[i].codigo);
		printf("  Estado: %s\n", temp_array[i].estado == 0 ? "Disponible" : "Prestado");
		printf("--------------------\n");
	}
	
	free(temp_array); // Liberar la memoria del arreglo temporal
}

void guardar_datos() {
	// ... (resto de la función igual) ...
	FILE *fp = fopen(FILENAME, "w");
	if (fp == NULL) {
		printf("ERROR: No se pudo abrir el archivo para guardar datos.\n");
		return;
	}
	
	fprintf(fp, "%d\n", num_libros_actual);
	NodoLibro *actual = lista_libros;
	while (actual != NULL) {
		fprintf(fp, "%s\n%s\n%s\n%d\n",
				actual->datos.titulo,
				actual->datos.autor,
				actual->datos.codigo,
				actual->datos.estado);
		actual = actual->siguiente;
	}
	
	fclose(fp);
	printf("Datos guardados exitosamente en %s.\n", FILENAME);
}

static void cargar_datos() { // <-- Ahora es static aquí, como una función auxiliar
	FILE *fp = fopen(FILENAME, "r");
	if (fp == NULL) {
		printf("Advertencia: No se encontraron datos previos (%s). Iniciando con biblioteca vacia.\n", FILENAME);
		num_libros_actual = 0;
		return;
	}
	
	liberar_memoria(); // Vaciar la lista actual antes de cargar una nueva
	
	int num_a_cargar;
	fscanf(fp, "%d\n", &num_a_cargar);
	
	Libro temp_libro;
	for (int i = 0; i < num_a_cargar; i++) {
		fgets(temp_libro.titulo, MAX_STR, fp);
		temp_libro.titulo[strcspn(temp_libro.titulo, "\n")] = 0;
		
		fgets(temp_libro.autor, MAX_STR, fp);
		temp_libro.autor[strcspn(temp_libro.autor, "\n")] = 0;
		
		fgets(temp_libro.codigo, MAX_STR, fp);
		temp_libro.codigo[strcspn(temp_libro.codigo, "\n")] = 0;
		
		fscanf(fp, "%d\n", &temp_libro.estado);
		
		agregar_libro_a_lista(temp_libro);
	}
	
	fclose(fp);
	printf("Datos cargados exitosamente desde %s (%d libros).\n", FILENAME, num_libros_actual);
}

void gestionar_prestamos_activos() {
	// ... (resto de la función igual) ...
	int encontrados = 0;
	NodoLibro *actual = lista_libros;
	printf("\n--- Prestamos Activos ---\n");
	while (actual != NULL) {
		if (actual->datos.estado == 1) { // Si el libro está prestado
			printf("  Titulo: %s, Autor: %s, Codigo: %s\n",
				   actual->datos.titulo, actual->datos.autor, actual->datos.codigo);
			encontrados = 1;
		}
		actual = actual->siguiente;
	}
	if (!encontrados) {
		printf("No hay prestamos activos en este momento.\n");
	}
}

void liberar_memoria() {
	// ... (resto de la función igual) ...
	NodoLibro *actual = lista_libros;
	NodoLibro *siguiente;
	while (actual != NULL) {
		siguiente = actual->siguiente;
		free(actual);
		actual = siguiente;
	}
	lista_libros = NULL;
	num_libros_actual = 0;
	printf("Memoria de la lista enlazada liberada.\n");
}
