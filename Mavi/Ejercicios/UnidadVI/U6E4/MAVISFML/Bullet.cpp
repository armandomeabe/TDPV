#include "Bullet.h"

Bullet::Bullet(float radius, const sf::Vector2f& position)
    : BaseObject("../../Res/bullet_hole.png") // Suponiendo que tienes una textura para la bala
{
    SetPosition(position);  // Establecemos la posici�n de la bala donde el jugador hace clic
    _speed = 500.0f;  // Establecemos la velocidad de la bala
    SetScale(0.1f);  // Puedes ajustar el tama�o de la bala aqu�
}

void Bullet::Update(float dt) {
    // Movimiento de la bala: movemos la bala en la direcci�n Y negativa (hacia arriba)
    sf::Vector2f velocity(0.0f, -_speed);  // Velocidad de la bala hacia arriba
    SetVelocity(velocity);  // Actualizamos la velocidad

    // Actualizamos la posici�n y la l�gica de movimiento (llama a la funci�n Update de BaseObject)
    BaseObject::Update(dt);
}