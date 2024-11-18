#include "Crosshair.h"
#include <iostream>

// Definición del tamaño deseado para la mira
const sf::Vector2f Crosshair::size = sf::Vector2f(50.f, 50.f); // Ajusta el tamaño según sea necesario

Crosshair::Crosshair(const std::string& texturePath) {
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Error al cargar la textura desde: " << texturePath << std::endl;
        return;
    }
    sprite.setTexture(texture);
    sprite.setScale(
        size.x / texture.getSize().x,
        size.y / texture.getSize().y
    );
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / static_cast<float>(2));

    sf::Vector2u size = texture.getSize();
    std::cout << "Tamaño de la textura del crosshair: " << size.x << "x" << size.y << std::endl;
}

Crosshair::Crosshair(const sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setScale(
        size.x / texture.getSize().x,
        size.y / texture.getSize().y
    );
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

    sf::Vector2u size = texture.getSize();
    std::cout << "Tamaño de la textura del crosshair: " << size.x << "x" << size.y << std::endl;
}

void Crosshair::updatePosition(const sf::RenderWindow& window) {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    sprite.setPosition(mousePos);
}

void Crosshair::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}