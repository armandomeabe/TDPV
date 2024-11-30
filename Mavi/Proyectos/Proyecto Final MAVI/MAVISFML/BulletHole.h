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
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Sprite bulletHoleSprite;
    float elapsedTime = 0.f;
    float lifetTime = 2.f;
};

#endif