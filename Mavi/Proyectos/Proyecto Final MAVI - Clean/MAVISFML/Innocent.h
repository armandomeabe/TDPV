#ifndef INNOCENT_H
#define INNOCENT_H

#include "Character.h"

class Innocent : public Character
{
public:
    Innocent(float x = 0, float y = 0, const std::string& texturePath = "");
    ~Innocent() = default;

    void flee(); // Método de ejemplo
};

#endif // INNOCENT_H
