#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Enemy : public Character {
public:
    // Constructor que recibe la textura, la posición y la escala
    Enemy(const sf::Texture& texture, float x, float y, float scale = 1.f);

    // Comprobar si un punto está dentro del sprite
    bool contains(const sf::Vector2f& point) const;

protected:
    // Aquí podemos añadir métodos adicionales o sobrecargar alguno de la clase base si es necesario

private:
    // Aquí puedes agregar atributos específicos si los necesitas para Enemy
};

#endif // ENEMY_H
