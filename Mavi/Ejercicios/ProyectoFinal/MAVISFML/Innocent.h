#ifndef INNOCENT_H
#define INNOCENT_H

#include <SFML/Graphics.hpp>
#include "Character.h"

class Innocent : public Character {
public:
    Innocent(const sf::Texture& texture, sf::Vector2f position);
    
    void update(sf::Time deltaTime) override;
    void draw(sf::RenderWindow& window) const;

private:
    // cri cri
};

#endif