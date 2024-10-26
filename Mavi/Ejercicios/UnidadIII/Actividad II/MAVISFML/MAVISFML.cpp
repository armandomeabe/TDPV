//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

//////Variables//////
Texture textureBlack, textureWhite;
Sprite board[8][8]; // después de hacer una cantidad industrial de instancias de Sprite me acordé de los arreglos

///Punto de entrada a la aplicación///
int main() {

    // Cargo las texturas de los archivos
    if (!textureBlack.loadFromFile("D:\\Developer\\FICH\\TDPV\\Mavi\\Ejercicios\\res\\chessb.png")) {
        std::cerr << "Error: No se pudo cargar el archivo chessb.png" << std::endl;
        // Resulta que texture...loadFromFile devuelve bool para indicar si pudo o no pudo cargar la textura, y es muy útil para hacer esto.
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
            if ((i + j) % 2 == 0) { //fila + columna es par o impar? ejemplo fila 2 columna 1 = 3 impar, si nos corremos para un costado o para arriba o abajo si o si va a dar par. Y viceversa.
                board[i][j].setTexture(textureWhite);
            }
            else {
                board[i][j].setTexture(textureBlack);
            }
            // Establecemos la posición de cada casilla y usamos la escala en X y en Y para que nos entren todas las casillas en la ventana
            // por qué tengo dos escalas (x e y)? porque la ventana no es cuadrada entonces son diferentes
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
            // Este era un intento de que mientras la app se esté "re-dibujando" deje de loopear y usar el 100% del procesador
            // pero lo hace de todos modos.
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