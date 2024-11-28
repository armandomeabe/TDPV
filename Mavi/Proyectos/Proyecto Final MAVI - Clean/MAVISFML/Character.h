#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

class Character
{
public:
    Character(float x = 0, float y = 0, const std::string& texturePath = "");
    virtual ~Character() = default;

    // M�todos para obtener y ajustar la posici�n
    float getX() const;
    float getY() const;
    void setPosition(float x, float y);

    // M�todos para manejar la textura
    const std::string& getTexturePath() const;
    void setTexturePath(const std::string& texturePath);

protected:
    float posX;                   // Posici�n X del personaje
    float posY;                   // Posici�n Y del personaje
    std::string texturePath;      // Ruta de la textura asociada
};

#endif // CHARACTER_H
