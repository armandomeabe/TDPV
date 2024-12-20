#pragma once
#include "BaseObject.h"

class Bullet : public BaseObject {
public:
    Bullet(float radius, const sf::Vector2f& position);
    void Update(float dt) override;  // Sobreescribimos el m�todo Update para la l�gica de la bala

private:
    float _speed;  // Velocidad de la bala
};
