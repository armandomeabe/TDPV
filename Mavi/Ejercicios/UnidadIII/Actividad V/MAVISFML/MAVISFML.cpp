//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

//////Variables//////
Texture texture;
Sprite sprite;

///Punto de entrada a la aplicación///
int main() {
    // Cargamos la textura del archivo (cualquiera que no sea el círculo rojo, elegí la plataforma cuadrada)
    if (!texture.loadFromFile("D:\\Developer\\FICH\\TDPV\\Mavi\\Ejercicios\\res\\plataforma.jpg")) {
        std::cerr << "Error: No se pudo cargar el archivo plataforma.jpg" << std::endl;
        return -1;
    }

    // Creamos la ventana
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Rotación del Sprite");

    // Configuramos el sprite
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2); // Establecemos el origen en el centro
    sprite.setPosition(400, 300); // Centramos el sprite en la ventana

    // Loop principal
    while (App.isOpen())
    {
        // Procesamos los eventos
        sf::Event event;
        while (App.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                App.close();
        }

        // Rotamos el sprite
        sprite.rotate(1.0f / 100); // Rota el sprite 1/100 grado por frame. Era 1 grado por frame pero giraba rapidísimo por eso la división.

        // Limpiamos la ventana
        App.clear();

        // Dibujamos el sprite
        App.draw(sprite);

        // Mostramos la ventana
        App.display();
    }

    return 0;
}