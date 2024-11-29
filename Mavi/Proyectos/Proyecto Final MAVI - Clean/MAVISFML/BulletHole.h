#pragma once
#ifndef BULLETHOLE_H
#define BULLETHOLE_H

#include <SFML/Graphics.hpp>

class BulletHole : public sf::Drawable {
public:
    BulletHole(sf::Texture& texture, const sf::Vector2f& position);

    void Update(float deltaTime);
    bool IsExpired() const;

protected:
    // Método de dibujo que SFML llamará
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Sprite bulletHoleSprite;
    float m_elapsedTime = 0.f;
    float m_lifetime = 2.f;  // Tiempo de vida del agujero de bala
};

#endif