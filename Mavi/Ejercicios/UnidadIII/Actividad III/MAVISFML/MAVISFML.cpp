//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

//////Variables//////
Texture textureBackground;
Sprite spriteBackground;

///Punto de entrada a la aplicación///
int main() {
    // Cargamos la textura del archivo de fondo
    if (!textureBackground.loadFromFile("D:\\Developer\\FICH\\TDPV\\Mavi\\Ejercicios\\res\\fondo.jpg")) {
        std::cerr << "Error: No se pudo cargar el archivo fondo.jpg" << std::endl;
        return -1;
    }

    // Creamos la ventana
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Fondo del Videojuego");

    // Configuramos el sprite del fondo
    spriteBackground.setTexture(textureBackground);

    // Calculamos la escala necesaria para ajustar la imagen al tamaño de la ventana
    float scaleX = 800.0f / textureBackground.getSize().x;
    float scaleY = 600.0f / textureBackground.getSize().y;

    // Aplicamos la escala
    spriteBackground.setScale(scaleX, scaleY);

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

        // Dibujamos el fondo
        App.draw(spriteBackground);

        // Mostramos la ventana
        App.display();
    }

    return 0;
}