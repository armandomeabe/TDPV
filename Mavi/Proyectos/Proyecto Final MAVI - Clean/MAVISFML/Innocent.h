#ifndef INNOCENT_H
#define INNOCENT_H

#include "Character.h"

class Innocent : public Character {
public:
    // Constructor que recibe la textura, la posici�n y la escala
    Innocent(const sf::Texture& texture, float x, float y, float scale = 1.f);

    // Comprobar si un punto est� dentro del sprite
    bool contains(const sf::Vector2f& point) const;
};

#endif // INNOCENT_H
