#include "color.h"
#include "vertex2.h"
#include <vector>
#include <SDL.h>
#include <random>
#include <iterator>

// Constantes
const int width = 800;
const int height = 400;
Color whiteColor(255, 255, 255); // Color de las células
Color clearColor(0, 0, 0);  // Color del fondo
const int cellSize = 1;  // Tamaño de cada célula en píxeles
const int patternsQuantity = 500; //Cantidad de patrones a desplegar

int seed[patternsQuantity * 3];
int cells[width][height];
std::vector<Color> framebuffer;

int pulsar[48][48] = {
                {0,0,1,1,1,0,0,0,1,1,1,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0},
                {1,0,0,0,0,1,0,1,0,0,0,0,1},
                {1,0,0,0,0,1,0,1,0,0,0,0,1},
                {1,0,0,0,0,1,0,1,0,0,0,0,1},
                {0,0,1,1,1,0,0,0,1,1,1,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,1,1,1,0,0,0,1,1,1,0,0},
                {1,0,0,0,0,1,0,1,0,0,0,0,1},
                {1,0,0,0,0,1,0,1,0,0,0,0,1},
                {1,0,0,0,0,1,0,1,0,0,0,0,1},
                {0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,1,1,1,0,0,0,1,1,1,0,0},
};

int* generateSeed(){
    for (int i = 0; i < patternsQuantity; i++){
        int pattern = rand()%(15-1 + 1) + 1;
        int xPosition = rand()%(width + 1);
        int yPosition = rand()%(height + 1);
        seed[i*3] = pattern;
        seed[i*3 + 1] = xPosition;
        seed[i*3 + 2] = yPosition;
    }
    return seed;
}

void clear(const Color& clearColor) {
    framebuffer.resize(width * height);
    fill(framebuffer.begin(), framebuffer.end(), clearColor);
}

// Function to generate the pattern at the specified position
void generatePattern(int patternChoice, int startX, int startY) {

    // Check the pattern choice and set the cells accordingly
    switch (patternChoice) {
        case 1: // Glider
            cells[startX][startY] = 1;
            cells[startX + 1][startY] = 1;
            cells[startX + 2][startY] = 1;
            cells[startX + 2][startY - 1] = 1;
            cells[startX + 1][startY - 2] = 1;
            break;
        case 2: // Collision
            cells[startX][startY] = 1;
            cells[startX + 1][startY] = 1;
            cells[startX + 4][startY] = 1;
            cells[startX + 5][startY] = 1;
            cells[startX][startY + 1] = 1;
            cells[startX + 5][startY + 1] = 1;
            cells[startX + 5][startY + 2] = 1;
            cells[startX + 1][startY + 3] = 1;
            cells[startX + 4][startY + 3] = 1;
            break;
        case 3: // Blinker
            cells[startX][startY] = 1;
            cells[startX][startY + 1] = 1;
            cells[startX][startY + 2] = 1;
            break;
        case 4: // Lightweight Spaceship (LWSS)
            cells[startX][startY] = 1;
            cells[startX + 1][startY] = 1;
            cells[startX + 3][startY] = 1;
            cells[startX + 4][startY] = 1;
            cells[startX + 2][startY + 1] = 1;
            cells[startX + 3][startY + 1] = 1;
            cells[startX][startY - 1] = 1;
            cells[startX + 1][startY - 1] = 1;
            cells[startX + 2][startY - 1] = 1;
            cells[startX + 3][startY - 1] = 1;
            cells[startX + 1][startY - 2] = 1;
            cells[startX + 2][startY - 2] = 1;
            break;
        case 5: //pulsar

            // Copy the pulsar pattern to the cells array at the specified position
            for (int x = 0; x < 13; ++x) {
                for (int y = 0; y < 13; ++y) {
                    cells[startX + x][startY + y] = pulsar[x][y];
                }
            }
            break;

        case 6: //block
            cells[startX][startY] = 1;
            cells[startX + 1][startY] = 1;
            cells[startX + 1][startY - 1] = 1;
            cells[startX][startY - 1] = 1;
            break;

        case 7: //beehive
            cells[startX][startY] = 1;
            cells[startX + 3][startY] = 1;
            cells[startX + 1][startY - 1] = 1;
            cells[startX + 2][startY - 1] = 1;
            cells[startX + 1][startY + 1] = 1;
            cells[startX + 2][startY + 1] = 1;
            break;

        case 8: //loaf
            cells[startX][startY] = 1;
            cells[startX + 3][startY] = 1;
            cells[startX + 1][startY + 1] = 1;
            cells[startX + 3][startY + 1] = 1;
            cells[startX + 2][startY + 2] = 1;
            cells[startX + 1][startY - 1] = 1;
            cells[startX + 2][startY - 1] = 1;
            break;

        case 9: //boat
            cells[startX][startY] = 1;
            cells[startX + 1][startY] = 1;
            cells[startX][startY + 1] = 1;
            cells[startX + 2][startY + 1] = 1;
            cells[startX + 1][startY + 2] = 1;
            break;

        case 10: //tub
            cells[startX][startY] = 1;
            cells[startX + 2][startY] = 1;
            cells[startX +1][startY - 1] = 1;
            cells[startX +1][startY + 1] = 1;
            break;

        case 11: //toad
            cells[startX][startY] = 1;
            cells[startX][startY + 1] = 1;
            cells[startX + 1][startY + 2] = 1;
            cells[startX + 2][startY - 1] = 1;
            cells[startX + 3][startY] = 1;
            cells[startX + 3][startY - 1] = 1;
            break;

        case 12: //beacon
            cells[startX][startY] = 1;
            cells[startX + 1][startY] = 1;
            cells[startX + 1][startY + 1] = 1;
            cells[startX][startY + 1] = 1;
            cells[startX + 2][startY + 2] = 1;
            cells[startX + 2][startY + 3] = 1;
            cells[startX + 3][startY + 2] = 1;
            cells[startX + 3][startY + 3] = 1;
            break;

        case 13: //penta-decathlon
            cells[startX][startY] = 1;
            cells[startX - 1][startY + 1] = 1;
            cells[startX][startY + 1] = 1;
            cells[startX + 1][startY + 1] = 1;
            cells[startX - 1][startY + 4] = 1;
            cells[startX][startY + 4] = 1;
            cells[startX + 1][startY + 4] = 1;
            cells[startX - 1][startY + 6] = 1;
            cells[startX - 1][startY + 7] = 1;
            cells[startX + 1][startY + 6] = 1;
            cells[startX + 1][startY + 7] = 1;
            cells[startX - 1][startY + 9] = 1;
            cells[startX][startY + 9] = 1;
            cells[startX + 1][startY + 9] = 1;
            cells[startX - 1][startY + 12] = 1;
            cells[startX][startY + 12] = 1;
            cells[startX + 1][startY + 12] = 1;
            cells[startX][startY + 13] = 1;
            break;
        
        case 14: //MWSS
            cells[startX][startY] = 1;
            cells[startX + 1][startY] = 1;
            cells[startX + 2][startY] = 1;
            cells[startX + 4][startY] = 1;
            cells[startX + 5][startY] = 1;
            cells[startX + 3][startY - 1] = 1;
            cells[startX + 4][startY - 1] = 1;
            cells[startX][startY + 1] = 1;
            cells[startX + 1][startY + 1] = 1;
            cells[startX + 2][startY + 1] = 1;
            cells[startX + 3][startY + 1] = 1;
            cells[startX + 4][startY + 1] = 1;
            cells[startX + 1][startY + 2] = 1;
            cells[startX + 2][startY + 2] = 1;
            cells[startX + 3][startY + 2] = 1;
        
        case 15: //HWSS
            cells[startX][startY] = 1;
            cells[startX + 6][startY] = 1;
            cells[startX + 1][startY - 1] = 1;
            cells[startX + 2][startY - 1] = 1;
            cells[startX + 3][startY - 1] = 1;
            cells[startX + 4][startY - 1] = 1;
            cells[startX + 5][startY - 1] = 1;
            cells[startX + 6][startY - 1] = 1;
            cells[startX + 6][startY + 1] = 1;
            cells[startX][startY + 2] = 1;
            cells[startX + 5][startY + 2] = 1;
            cells[startX + 2][startY + 3] = 1;
            cells[startX + 3][startY + 3] = 1;
        // Add more cases for other patterns here

        default:
            std::cout << "Invalid pattern choice. No pattern generated." << std::endl;
    }
}

void createFrameBuffer(){
    clear(clearColor);

    // Estado inicial aleatorio
    generateSeed();
    for (int element = 0; element < patternsQuantity; element++) {
        generatePattern(seed[element * 3], seed[element*3 + 1], seed[element*3 + 2]);
    }
}

void point(const Vertex2 vertex, const Color color) {
    

    int x = static_cast<int>(vertex.x);
    int y = static_cast<int>(vertex.y);

    if (x >= 0 && x < width && y >= 0 && y < height) {
        int index = y * width + x;
        framebuffer[index] = color;
    }
}


int countAliveNeighbors(int x, int y) {
    int count = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue; // Saltar la célula actual
            int nx = x + dx;
            int ny = y + dy;
            // Asegurarse de que no nos salimos de los límites de la matriz
            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                // Sumar al contador si la célula vecina está viva
                count += cells[nx][ny];
            }
        }
    }
    return count;
}

void renderGame(SDL_Renderer* renderer) {
    // Limpiar el framebuffer (no llamamos a la función clear)
    for (int x = 0; x <= width; x++) {
        for (int y = 0; y <= height; y++) {
            cells[x][y] == 1 ? point(Vertex2{x, y}, whiteColor) : point(Vertex2{x, y}, clearColor);
        }
    }
}

void updateGame(SDL_Renderer* renderer) {
    // Crear una copia temporal de la matriz de células para aplicar las reglas sin modificar la original
    int newCells[width][height];

    // Aplicar las reglas del "Game of Life" a todas las células
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            int aliveNeighbors = countAliveNeighbors(x, y);
            if (cells[x][y]) {
                // La célula está viva, aplicar reglas de sobrevivencia o muerte
                if (aliveNeighbors < 2 || aliveNeighbors > 3) {
                    newCells[x][y] = 0; // Muere por underpopulation o overpopulation
                } else {
                    newCells[x][y] = 1; // Sobrevive
                }
            } else {
                // La célula está muerta, aplicar reglas de reproducción
                if (aliveNeighbors == 3) {
                    newCells[x][y] = 1; // Nace por reproducción
                } else {
                    newCells[x][y] = 0; // Sigue muerta
                }
            }
        }
    }

    // Actualizar la matriz de células con la copia temporal
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            cells[x][y] = newCells[x][y];
        }
    }

    renderGame(renderer);
}

void renderBuffer(SDL_Renderer* renderer) {
    // Create a texture
    SDL_Texture* texture = SDL_CreateTexture(
        renderer, 
        SDL_PIXELFORMAT_RGB24,
        SDL_TEXTUREACCESS_STREAMING,
        width, 
        height
    );

    // Update the texture with the pixel data from the framebuffer
    SDL_UpdateTexture(
        texture, 
        NULL, 
        framebuffer.data(), 
        width * sizeof(Color)
    );

    // Clear the renderer
    SDL_RenderClear(renderer);

    // Copy the texture to the renderer
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Destroy the texture
    SDL_DestroyTexture(texture);
}