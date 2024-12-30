#pragma once

#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Crosshair {
public:
    // El dibujo de la mira
    Sprite sprite;

    // Constructor por defecto
    Crosshair();

    // Cu�n grande queremos que sea la mira
    static const Vector2f size;

    // Constructor para la mira
    Crosshair(const Texture& texture);

    // Actualiza la posici�n de la mira seg�n el mouse
    void updatePosition(const RenderWindow& window);

    // Dibuja la mira en la ventana
    void draw(RenderWindow& window);

private:
    sf::Texture crosshairTexture;
};

#endif // CROSSHAIR_H
