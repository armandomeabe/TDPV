#include "Crosshair.h"

// Inicialización del tamaño estático de la mira
const Vector2f Crosshair::size = Vector2f(32.f, 32.f);

// Constructor para la mira
Crosshair::Crosshair(const Texture& texture) {
    sprite.setTexture(texture); // Le ponemos la textura a la mira
    // Escalamos la mira para que tenga el tamaño que queremos
    sprite.setScale(
        size.x / texture.getSize().x,
        size.y / texture.getSize().y
    );

    // Colocamos el origen en el centro para que apunte bien
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

Crosshair::Crosshair() {
    // Cargar textura crosshair
    if (!crosshairTexture.loadFromFile("../Recursos/Assets/crosshair.png"))
    {
        throw std::runtime_error("Failed to load Crosshair texture.");
    }

    sprite.setTexture(crosshairTexture); // Le ponemos la textura a la mira
    // Escalamos la mira para que tenga el tamaño que queremos
    sprite.setScale(
        size.x / crosshairTexture.getSize().x,
        size.y / crosshairTexture.getSize().y
    );

    // Colocamos el origen en el centro para que apunte bien
    sprite.setOrigin(crosshairTexture.getSize().x / 2, crosshairTexture.getSize().y / 2);
}

// Actualiza la posición de la mira según el mouse
void Crosshair::updatePosition(const RenderWindow& window) {
    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
    sprite.setPosition(mousePos);
}

// Dibuja la mira en la ventana
void Crosshair::draw(RenderWindow& window) {
    window.draw(sprite);
}
