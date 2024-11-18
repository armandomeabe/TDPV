#include "Character.h"
#include <cstdlib>

const sf::Vector2f Character::defaultSize(64, 64); // Tamaño por defecto

Character::Character(const sf::Texture& texture, const sf::Vector2f& size) {
    sprite.setTexture(texture);
    sprite.setScale(
        size.x / texture.getSize().x,
        size.y / texture.getSize().y
    );
    setRandomPosition();

    //// Asignar una velocidad aleatoria
    //float speedX = static_cast<float>((std::rand() % 100) - 50);
    //float speedY = static_cast<float>((std::rand() % 100) - 50);
    //velocity = sf::Vector2f(speedX, speedY);
}

void Character::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::FloatRect Character::getBounds() const {
    return sprite.getGlobalBounds();
}

void Character::setRandomPosition() {
    //float x = static_cast<float>(std::rand() % (800 - static_cast<int>(defaultSize.x)));
    //float y = static_cast<float>(std::rand() % (600 - static_cast<int>(defaultSize.y)));
    //sprite.setPosition(x, y);
}