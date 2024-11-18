#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include <string>

class HUD {
public:
    HUD();

    void update(int lives, int score);
    void draw(sf::RenderWindow& window);

private:
    sf::Font font;
    sf::Text livesText;
    sf::Text scoreText;

    void initializeText(sf::Text& text, const sf::Font& font, unsigned int size, const sf::Color& color, const sf::Vector2f& position);
};

#endif