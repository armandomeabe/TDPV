#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Enemy : public Character {
public:
    // Constructor que recibe la textura, la posici�n y la escala
    Enemy(const sf::Texture& texture, float x, float y, float scale = 1.f);

    // M�todos adicionales espec�ficos de Enemy pueden ir aqu�...
    void setPosition(float x, float y);  // Establece la posici�n del enemigo

    // Comprobar si un punto est� dentro del sprite
    bool contains(const sf::Vector2f& point) const;

protected:
    // Aqu� podemos a�adir m�todos adicionales o sobrecargar alguno de la clase base si es necesario

private:
    // Aqu� puedes agregar atributos espec�ficos si los necesitas para Enemy
};

#endif // ENEMY_H
