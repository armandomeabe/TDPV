#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

class Character
{
public:
    Character(float x = 0, float y = 0, const std::string& texturePath = "");
    virtual ~Character() = default;

    // Métodos para obtener y ajustar la posición
    float getX() const;
    float getY() const;
    void setPosition(float x, float y);

    // Métodos para manejar la textura
    const std::string& getTexturePath() const;
    void setTexturePath(const std::string& texturePath);

protected:
    float posX;                   // Posición X del personaje
    float posY;                   // Posición Y del personaje
    std::string texturePath;      // Ruta de la textura asociada
};

#endif // CHARACTER_H
