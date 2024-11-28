#include "Enemy.h"
#include <iostream>

Enemy::Enemy(float x, float y, const std::string& texturePath)
    : Character(x, y, texturePath) {}

void Enemy::attack()
{
    std::cout << "Enemy at (" << getX() << ", " << getY() << ") is attacking with texture: " << getTexturePath() << "\n";
}
