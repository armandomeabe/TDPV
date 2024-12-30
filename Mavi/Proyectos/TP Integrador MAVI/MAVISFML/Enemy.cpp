#include "Enemy.h"

// Constructor que pasa la textura a la clase base (Character) y recibe la posición y la escala
Enemy::Enemy(const sf::Texture& texture, float x, float y, float scale) : Character(texture, 5) {
    setPosition(x, y);  // Establecer la posición
    getSprite().setScale(scale, scale);  // Establecer la escala
}

// Comprobar si un punto está dentro del sprite
bool Enemy::contains(const sf::Vector2f& point) const {
    return getGlobalBounds().contains(point);  // Llamamos al método de la clase base para obtener los límites
}
