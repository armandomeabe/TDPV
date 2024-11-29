#include "Innocent.h"

// Constructor que pasa la textura a la clase base (Character) y recibe la posici�n y la escala
Innocent::Innocent(const sf::Texture& texture, float x, float y, float scale) : Character(texture) {
    setPosition(x, y);  // Establecer la posici�n
    getSprite().setScale(scale, scale);  // Establecer la escala
}

// Comprobar si un punto est� dentro del sprite
bool Innocent::contains(const sf::Vector2f& point) const {
    return getGlobalBounds().contains(point);  // Llamamos al m�todo de la clase base para obtener los l�mites
}