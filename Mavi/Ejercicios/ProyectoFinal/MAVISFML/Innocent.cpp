#include "Innocent.h"

Innocent::Innocent(const sf::Texture& texture, sf::Vector2f position)
    : Character(texture, Character::defaultSize) {
    sprite.setPosition(position);
}

void Innocent::update(sf::Time deltaTime) {
    // no se mueve
}

void Innocent::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}