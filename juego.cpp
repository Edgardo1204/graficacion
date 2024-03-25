#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstdlib>  
#include <ctime>   

const int WIDTH = 20;  
const int HEIGHT = 4;  

std::mutex mtx; 

void printPlane(char plane[HEIGHT][WIDTH]) {
    std::lock_guard<std::mutex> lock(mtx); 
    system("cls"); 

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            std::cout << plane[i][j];
        }
        std::cout << std::endl;
    }
}

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
    }
}

int main() {
    char plane[HEIGHT][WIDTH]; 
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            plane[i][j] = ' ';
        }
    }

    std::thread t1(translate, std::ref(plane)); // Hilo para la traslación
    t1.join();

    return 0;
}
