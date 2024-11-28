#include "Innocent.h"
#include <iostream>

Innocent::Innocent(float x, float y, const std::string& texturePath)
    : Character(x, y, texturePath) {}

void Innocent::flee()
{
    std::cout << "Innocent at (" << getX() << ", " << getY() << ") is fleeing with texture: " << getTexturePath() << "\n";
}
