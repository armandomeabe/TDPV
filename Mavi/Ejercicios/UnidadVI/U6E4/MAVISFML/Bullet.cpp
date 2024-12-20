#include "Bullet.h"

Bullet::Bullet(float radius, const sf::Vector2f& position)
    : BaseObject("../../Res/bullet_hole.png") {
    SetPosition(position);
    SetAcceleration(sf::Vector2f(0, 0));
    SetScale(0.1f);  // Tamaño de la bala
    manuallyObsolete = false;
}

void Bullet::Update(float dt) {
    _lifeTime += dt; // Incrementamos el tiempo de vida
    BaseObject::Update(dt);
}

bool Bullet::Obsolete() const {
    return manuallyObsolete || _lifeTime >= 1.0f; // La bala es obsoleta tras 1 segundo
}

void Bullet::SetManuallyObsolete()
{
    manuallyObsolete = true;
}