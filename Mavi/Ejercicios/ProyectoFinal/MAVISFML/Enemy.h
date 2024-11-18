#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Character.h"

class Enemy : public Character {
public:
    Enemy(const sf::Texture& texture, sf::Vector2f position);

    void update(sf::Time deltaTime) override;
    void draw(sf::RenderWindow& window) const;

private:
    //
};

#endif