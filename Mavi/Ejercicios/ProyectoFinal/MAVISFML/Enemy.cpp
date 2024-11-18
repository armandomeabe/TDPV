#include "Enemy.h"

Enemy::Enemy(const sf::Texture& texture, sf::Vector2f position)
    : Character(texture, Character::defaultSize) { 
    sprite.setPosition(position);
}

void Enemy::update(sf::Time deltaTime) {
    // No se mueve
}

void Enemy::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}