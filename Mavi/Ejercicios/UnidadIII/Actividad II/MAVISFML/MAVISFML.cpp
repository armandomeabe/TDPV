//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

//////Variables//////
Texture textureBlack, textureWhite;
Sprite board[8][8];

///Punto de entrada a la aplicación///
int main() {

    // Cargo las texturas de los archivos
    if (!textureBlack.loadFromFile("D:\\Developer\\FICH\\TDPV\\Mavi\\Ejercicios\\res\\chessb.png")) {
        std::cerr << "Error: No se pudo cargar el archivo chessb.png" << std::endl;
        return -1;
    }
    if (!textureWhite.loadFromFile("D:\\Developer\\FICH\\TDPV\\Mavi\\Ejercicios\\res\\chessw.png")) {
        std::cerr << "Error: No se pudo cargar el archivo chessw.png" << std::endl;
        return -1;
    }

    // Creo la ventana
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Tablero de Ajedrez");

    // Calculamos la escala necesaria para ajustar las casillas al tamaño de la ventana
    // por qué? porque sino se me "escapa de la ventana" el tablero
    float scaleX = 800.0f / (8 * 128.0f); // Escala en el eje X
    float scaleY = 600.0f / (8 * 128.0f); // Escala en el eje Y

    // Configuramos el tablero de ajedrez
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            // Alternamos las texturas para crear el patrón intercalado
            if ((i + j) % 2 == 0) { //fila + columna es par o impar?
                board[i][j].setTexture(textureWhite);
            }
            else {
                board[i][j].setTexture(textureBlack);
            }
            // Establecemos la posición de cada casilla y usamos la escala en X y en Y para que nos entren todas las casillas en la ventana
            board[i][j].setPosition(i * 128 * scaleX, j * 128 * scaleY);

            // Aplicamos la escala
            board[i][j].setScale(scaleX, scaleY);
        }
    }

    // Loop principal
    while (App.isOpen())
    {
        // Procesamos los eventos
        sf::Event event;
        while (App.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                App.close();
        }

        // Limpiamos la ventana
        App.clear();

        // Dibujamos la escena
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                App.draw(board[i][j]);
            }
        }

        // Mostramos la ventana
        App.display();
    }

    return 0;
}