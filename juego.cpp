#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
<<<<<<< HEAD
#include <cstdlib>  
#include <ctime>   

const int WIDTH = 20;  
const int HEIGHT = 4;  

std::mutex mtx; 

void printPlane(char plane[HEIGHT][WIDTH]) {
    std::lock_guard<std::mutex> lock(mtx); 
    system("cls"); 
=======

const int WIDTH = 20;  // Ancho del plano
const int HEIGHT = 2;  // Dos líneas horizontales

std::mutex mtx; // Mutex para evitar condiciones de carrera al imprimir en la consola

// Función para imprimir el plano
void printPlane(char plane[HEIGHT][WIDTH]) {
    std::lock_guard<std::mutex> lock(mtx); // Bloquear el mutex para evitar condiciones de carrera
    system("cls"); // Limpiar la consola (compatible con sistemas Windows)
>>>>>>> 10acb119f7d3dfe8711d5953c1204a5f258f860b

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            std::cout << plane[i][j];
        }
        std::cout << std::endl;
    }
}

<<<<<<< HEAD
std::string generateRandomPattern() {
    std::string pattern;
    for (int i = 0; i < WIDTH; ++i) {
        pattern += (rand() % 2 == 0) ? '-' : ' '; // Generar aleatoriamente un guion o un espacio en blanco
    }
    return pattern;
}

// traslada las líneas hacia la izquierda y hacia la derecha
void translate(char plane[HEIGHT][WIDTH]) {
    int currentPos[HEIGHT]; 
    std::string patterns[HEIGHT]; 

    srand(time(0)); 

    
    for (int i = 0; i < HEIGHT; ++i) {
        currentPos[i] = (i % 2 == 0) ? WIDTH - 1 : 0;
        patterns[i] = generateRandomPattern();
    }

    while (true) {
        // Actualizar cada línea
        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                plane[i][j] = patterns[i][(currentPos[i] + j) % WIDTH]; 
            }

            if (i % 2 == 0) {
                --currentPos[i]; 
                if (currentPos[i] < 0) {
                    currentPos[i] = WIDTH - 1; // Volver al final del plano si se llega al inicio
                }
            } else {
                ++currentPos[i]; 
                if (currentPos[i] >= WIDTH) {
                    currentPos[i] = 0; // Volver al inicio del plano si se llega al final
                }
            }
        }

        printPlane(plane); // Imprimir el plano actualizado
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); 
=======
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
>>>>>>> 10acb119f7d3dfe8711d5953c1204a5f258f860b
    }
}

int main() {
<<<<<<< HEAD
    char plane[HEIGHT][WIDTH]; 
=======
    char plane[HEIGHT][WIDTH]; // Declarar el plano

    // Inicializar el plano con espacios en blanco
>>>>>>> 10acb119f7d3dfe8711d5953c1204a5f258f860b
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            plane[i][j] = ' ';
        }
    }

<<<<<<< HEAD
    std::thread t1(translate, std::ref(plane)); // Hilo para la traslación
=======
    std::thread t1(translate, std::ref(plane)); // Crear un hilo para la traslación

    // Esperar a que el hilo termine (esto nunca ocurrirá debido al bucle infinito en translate)
>>>>>>> 10acb119f7d3dfe8711d5953c1204a5f258f860b
    t1.join();

    return 0;
}
