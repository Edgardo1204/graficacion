#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

const int WIDTH = 20;  // Ancho del plano
const int HEIGHT = 2;  // Dos líneas horizontales

std::mutex mtx; // Mutex para evitar condiciones de carrera al imprimir en la consola

// Función para imprimir el plano
void printPlane(char plane[HEIGHT][WIDTH]) {
    std::lock_guard<std::mutex> lock(mtx); // Bloquear el mutex para evitar condiciones de carrera
    system("cls"); // Limpiar la consola (compatible con sistemas Windows)

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            std::cout << plane[i][j];
        }
        std::cout << std::endl;
    }
}

// Función para trasladar las líneas hacia la izquierda y hacia la derecha
void translate(char plane[HEIGHT][WIDTH]) {
    int currentPos1 = WIDTH - 1; // Posición actual del guion de la primera línea
    int currentPos2 = 0; // Posición actual del guion de la segunda línea

    while (true) {
        for (int j = 0; j < WIDTH; ++j) {
            plane[0][j] = (j >= currentPos1 - 4 && j <= currentPos1) ? '-' : ' '; // Línea 1 con guiones y espacios vacíos
            plane[1][j] = (j >= currentPos2 && j <= currentPos2 + 4) ? '-' : ' '; // Línea 2 con guiones y espacios vacíos
        }

        printPlane(plane); // Imprimir el plano actualizado
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Esperar un tiempo antes de la próxima traslación

        --currentPos1; // Mover la posición actual de la primera línea hacia la izquierda
        ++currentPos2; // Mover la posición actual de la segunda línea hacia la derecha

        // Si la posición actual de la primera línea es menor que 0, volver al final del plano
        if (currentPos1 < 0) {
            currentPos1 = WIDTH - 1;
        }

        // Si la posición actual de la segunda línea es mayor o igual al ancho del plano, volver al inicio del plano
        if (currentPos2 >= WIDTH) {
            currentPos2 = 0;
        }
    }
}

int main() {
    char plane[HEIGHT][WIDTH]; // Declarar el plano

    // Inicializar el plano con espacios en blanco
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            plane[i][j] = ' ';
        }
    }

    std::thread t1(translate, std::ref(plane)); // Crear un hilo para la traslación

    // Esperar a que el hilo termine (esto nunca ocurrirá debido al bucle infinito en translate)
    t1.join();

    return 0;
}
