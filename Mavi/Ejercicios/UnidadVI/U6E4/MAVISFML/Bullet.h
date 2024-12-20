#pragma once
#include "BaseObject.h"

class Bullet : public BaseObject {
public:
    Bullet(float radius, const sf::Vector2f& position);
    void Update(float dt) override;  // Sobreescribimos el método Update para la lógica de la bala
    bool Obsolete();

private:
    float _lifeTime; // vencimiento
    float _speed;  // Velocidad de la bala
};
