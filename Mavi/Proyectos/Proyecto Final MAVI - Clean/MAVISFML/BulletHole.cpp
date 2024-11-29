#include "BulletHole.h"

BulletHole::BulletHole(sf::Texture& texture, const sf::Vector2f& position)
{
    bulletHoleSprite.setTexture(texture);
    bulletHoleSprite.setScale(.5, .5);

    // Establecer la posición del agujero de bala
    bulletHoleSprite.setOrigin(bulletHoleSprite.getLocalBounds().width / 2,
        bulletHoleSprite.getLocalBounds().height / 2);
    bulletHoleSprite.setPosition(position);
}

void BulletHole::Update(float deltaTime)
{
    m_elapsedTime += deltaTime;
}

bool BulletHole::IsExpired() const
{
    return m_elapsedTime >= m_lifetime;
}

// Implementación del método draw
void BulletHole::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(bulletHoleSprite, states);  // Dibuja el sprite en la pantalla
}