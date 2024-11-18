#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>

class Character {
public:
    Character(const sf::Texture& texture, const sf::Vector2f& size);

    virtual void update(sf::Time deltaTime) = 0; // Método virtual puro
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;
    void setRandomPosition();

protected:
    sf::Sprite sprite;
    sf::Vector2f velocity;
    static const sf::Vector2f defaultSize;
};

#endif