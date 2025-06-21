# Sistema de Gestión de Biblioteca en C

## Descripción del Proyecto
Este proyecto implementa un sistema básico de gestión de biblioteca desarrollado en lenguaje C. Permite a los usuarios registrar nuevos libros, prestar y devolver libros, buscar libros por título o autor, listar todos los libros disponibles (con opción de ordenamiento), y visualizar los préstamos activos. La información de los libros se guarda y carga desde un archivo de texto plano para persistencia de datos.

## Integrantes y Roles
* **guaguei** - Arquitecto de Software / Desarrollador Principal (Realizó la mayor parte de la estructura del código)
* **collaborative-coder** - Ingeniero de Pruebas / Desarrollador de Control de Calidad (Realizó pruebas y modificaciones al código)

## Instrucciones para Compilar y Ejecutar

Este programa ha sido diseñado para ser compilado y ejecutado en sistemas operativos Windows y Linux.

### Requisitos Previos
Necesitarás tener un compilador de C instalado en tu sistema.
* **En Linux:** `gcc` (GNU Compiler Collection) suele venir preinstalado o puede instalarse fácilmente.
    * Para instalar `gcc` en sistemas basados en Debian/Ubuntu:
        ```bash
        sudo apt update
        sudo apt install build-essential
        ```
* **En Windows:** Se recomienda usar `MinGW-w64` o `MSYS2` para obtener `gcc`.
    * Descarga e instala `MinGW-w64` desde su sitio oficial (https://mingw-w64.org/doku.php/download). Asegúrate de añadir `gcc` al PATH del sistema durante la instalación o manualmente.

### Pasos para Compilar y Ejecutar

1.  **Descargar los archivos:**
    Asegúrate de tener los siguientes archivos en el mismo directorio:
    * `main.c`
    * `biblioteca.c`
    * `biblioteca.h`
    * `libros.txt` (Este archivo se creará automáticamente si no existe, o contendrá los datos iniciales de la biblioteca).

2.  **Abrir una Terminal o Símbolo del Sistema:**
    * **En Linux:** Abre una terminal (Ctrl+Alt+T).
    * **En Windows:** Abre el Símbolo del Sistema (CMD) o PowerShell.

3.  **Navegar al directorio del proyecto:**
    Usa el comando `cd` para ir al directorio donde guardaste los archivos. Por ejemplo, si los guardaste en `C:\Users\TuUsuario\Desktop\Biblioteca`:
    ```bash
    # En Windows
    cd C:\Users\TuUsuario\Desktop\Biblioteca
    # En Linux
    cd ~/Desktop/Biblioteca
    ```

4.  **Compilar el programa:**
    Ejecuta el siguiente comando en la terminal/símbolo del sistema:
    ```bash
    gcc main.c biblioteca.c -o biblioteca -Wall
    ```
    * `gcc`: Es el comando del compilador de C.
    * `main.c biblioteca.c`: Son los archivos fuente que se van a compilar.
    * `-o biblioteca`: Especifica el nombre del archivo ejecutable de salida. Puedes cambiar `biblioteca` por el nombre que desees.
    * `-Wall`: Habilita todas las advertencias (Warnings) para ayudarte a escribir un código más limpio y sin errores.

    Si la compilación es exitosa, no verás ningún mensaje de error y se creará un archivo ejecutable llamado `biblioteca` (en Linux) o `biblioteca.exe` (en Windows) en tu directorio actual.

5.  **Ejecutar el programa:**
    Una vez compilado, puedes ejecutar el programa con el siguiente comando:
    ```bash
    # En Linux
    ./biblioteca
    # En Windows
    biblioteca.exe
    ```

    El programa se iniciará y mostrará el menú principal del sistema de gestión de biblioteca en la consola. Sigue las instrucciones en pantalla para interactuar con el sistema.

### Notas Adicionales
* Los datos de los libros se guardarán automáticamente en el archivo `libros.txt` al salir del programa (opción 7 del menú).
* Si el archivo `libros.txt` no existe al iniciar el programa, se creará uno nuevo y la biblioteca iniciará vacía.