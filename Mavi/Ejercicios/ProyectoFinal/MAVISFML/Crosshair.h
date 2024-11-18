#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include <SFML/Graphics.hpp>
#include <string>

class Crosshair {
public:
    Crosshair(const std::string& texturePath); // Cambiado para aceptar una ruta
    Crosshair(const sf::Texture& texture);

    void updatePosition(const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

    static const sf::Vector2f size; // Tamaño deseado para la mira

private:
    sf::Sprite sprite; // El dibujo de la mira
    sf::Texture texture; // Almacena la textura cargada
};

#endif // CROSSHAIR_H