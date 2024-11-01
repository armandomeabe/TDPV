// Este código fue adaptado de una implementación Python encontrada en internet con ayuda de GPT 4o
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

// Constantes para el tamaño de la cuadrícula y de cada celda
const int GRID_WIDTH = 100;  // Número de celdas en la dirección horizontal
const int GRID_HEIGHT = 75;  // Número de celdas en la dirección vertical
const int CELL_SIZE = 10;    // Tamaño de cada celda en píxeles

// Función para contar el número de vecinos vivos alrededor de una celda dada
int countLiveNeighbors(const std::vector<std::vector<bool>>& grid, int x, int y) {
    int liveNeighbors = 0;

    // Iterar sobre los 8 vecinos posibles
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            // Ignorar la propia celda, solo contamos vecinos
            if (dx == 0 && dy == 0) continue;

            int nx = x + dx;  // Coordenada x del vecino
            int ny = y + dy;  // Coordenada y del vecino

            // Comprobar que el vecino está dentro de los límites de la cuadrícula
            if (nx >= 0 && nx < GRID_WIDTH && ny >= 0 && ny < GRID_HEIGHT) {
                // Incrementar el contador si el vecino está vivo
                liveNeighbors += grid[nx][ny] ? 1 : 0;
            }
        }
    }

    return liveNeighbors;
}

// Función para actualizar el estado de toda la cuadrícula a la siguiente generación
void updateGrid(std::vector<std::vector<bool>>& grid) {
    // Crear una copia de la cuadrícula actual para calcular la nueva generación
    std::vector<std::vector<bool>> newGrid = grid;

    // Iterar sobre cada celda de la cuadrícula
    for (int x = 0; x < GRID_WIDTH; ++x) {
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            // Contar los vecinos vivos de la celda actual
            int liveNeighbors = countLiveNeighbors(grid, x, y);

            // Aplicar las reglas del Juego de la Vida
            if (grid[x][y]) {
                // Una celda viva con menos de 2 o más de 3 vecinos vivos muere
                if (liveNeighbors < 2 || liveNeighbors > 3) {
                    newGrid[x][y] = false;
                }
                // Una celda viva con 2 o 3 vecinos vivos sigue viva (no se necesita hacer nada)
            }
            else {
                // Una celda muerta con exactamente 3 vecinos vivos nace
                if (liveNeighbors == 3) {
                    newGrid[x][y] = true;
                }
            }
        }
    }

    // Actualizar la cuadrícula con la nueva generación
    grid = newGrid;
}

int main() {
    // Crear una ventana para renderizar el juego
    RenderWindow window(VideoMode(GRID_WIDTH * CELL_SIZE, GRID_HEIGHT * CELL_SIZE), "Juego de la vida de Conway");

    // Inicializar la cuadrícula con valores aleatorios (celdas vivas o muertas)
    std::vector<std::vector<bool>> grid(GRID_WIDTH, std::vector<bool>(GRID_HEIGHT));
    for (int x = 0; x < GRID_WIDTH; ++x) {
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            // 15% de probabilidad de que una celda esté viva al inicio, jugar con este valor
            grid[x][y] = (rand() % 100) < 15;
        }
    }

    // Bucle principal de la aplicación
    while (window.isOpen()) {
        // Manejar eventos de la ventana
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();  // Cerrar la ventana si se recibe un evento de cierre
        }

        // Actualizar la cuadrícula a la siguiente generación
        updateGrid(grid);

        // Limpiar la ventana antes de dibujar
        window.clear(Color::Black);

        // Dibujar las celdas vivas
        for (int x = 0; x < GRID_WIDTH; ++x) {
            for (int y = 0; y < GRID_HEIGHT; ++y) {
                if (grid[x][y]) {
                    // Crear un rectángulo para representar la celda
                    RectangleShape cell(Vector2f(CELL_SIZE, CELL_SIZE));
                    cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                    cell.setFillColor(Color::White);  // Color blanco para celdas vivas
                    window.draw(cell);  // Dibujar la celda en la ventana
                }
            }
        }

        // Mostrar el contenido renderizado en la ventana
        window.display();

        // Añadir un pequeño retraso para controlar la velocidad de la simulación
        //sf::sleep(sf::milliseconds(100));
    }

    return 0;
}