#include "biblioteca.h" // Incluye nuestra cabecera para acceder a las funciones de la biblioteca 
#include <stdio.h>      // Para printf, scanf 
#include <stdlib.h>     // Para system (limpiar pantalla), exit 

// Prototipo de una funcion auxiliar para el main
void mostrar_menu();
static void limpiar_buffer_main(); // Auxiliar para limpiar buffer en main

int main() {
	int opcion;
	
	inicializar_sistema(); // Cargar los datos de la biblioteca al iniciar 
	
	do {
		mostrar_menu();
		printf("Ingrese su opcion: ");
		scanf("%d", &opcion);
		limpiar_buffer_main(); // Limpiar el buffer despues de leer un entero
		
		switch (opcion) {
		case 1:
			registrar_libro();
			break;
		case 2:
			prestar_devolver_libro(1); // 1 para prestar
			break;
		case 3:
			prestar_devolver_libro(0); // 0 para devolver
			break;
		case 4:
			buscar_libro();
			break;
		case 5:
			listar_libros();
			break;
		case 6:
			gestionar_prestamos_activos();
			break;
		case 7:
			guardar_datos(); // Guardar antes de salir
			liberar_memoria(); // Liberar la memoria de la lista enlazada
			printf("Gracias por usar el sistema de biblioteca. ¡Hasta luego!\n");
			break;
		default:
			printf("Opcion invalida. Por favor, intente de nuevo.\n");
			break;
		}
		printf("\nPresione Enter para continuar...");
		getchar(); // Esperar que el usuario presione Enter
		system("clear || cls"); // Limpiar pantalla (Linux/macOS || Windows)
	} while (opcion != 7);
	
	return 0;
}

// --- Implementacion de Funciones Auxiliares para main.c ---
void mostrar_menu() {
	printf("--- Sistema de Biblioteca ---\n");
	printf("1. Registrar nuevo libro\n");
	printf("2. Prestar libro\n");
	printf("3. Devolver libro\n");
	printf("4. Buscar libro por titulo/autor\n");
	printf("5. Listar todos los libros\n");
	printf("6. Ver prestamos activos\n");
	printf("7. Salir\n");
	printf("-----------------------------\n");
}

static void limpiar_buffer_main() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}
