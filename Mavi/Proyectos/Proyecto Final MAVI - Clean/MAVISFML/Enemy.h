#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Enemy : public Character
{
public:
    Enemy(float x = 0, float y = 0, const std::string& texturePath = "");
    ~Enemy() = default;

    void attack(); // Método de ejemplo
};

#endif // ENEMY_H
