#include "Character.h"

Character::Character(float x, float y, const std::string& texturePath)
    : posX(x), posY(y), texturePath(texturePath) {}

float Character::getX() const
{
    return posX;
}

float Character::getY() const
{
    return posY;
}

void Character::setPosition(float x, float y)
{
    posX = x;
    posY = y;
}

const std::string& Character::getTexturePath() const
{
    return texturePath;
}

void Character::setTexturePath(const std::string& texturePath)
{
    this->texturePath = texturePath;
}
