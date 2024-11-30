#include "Character.h"

// Constructor que recibe la textura y la establece en el sprite
Character::Character(const sf::Texture& texture, float lifeTime) {
    this->lifeTime = lifeTime;
    elapsedTime = 0;
    sprite.setTexture(texture);
}

// Establecer la posición del personaje
void Character::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

// Obtener la posición del personaje
sf::Vector2f Character::getPosition() const {
    return sprite.getPosition();
}

// Obtener los límites del sprite para la colisión
sf::FloatRect Character::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

// Método para dibujar el sprite
void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

sf::Sprite& Character::getSprite() {
    return sprite;  // Devolver la referencia al sprite
}

void Character::Update(float deltaTime)
{
    elapsedTime += deltaTime;
}

bool Character::IsExpired() const
{
    return elapsedTime >= lifeTime;
}