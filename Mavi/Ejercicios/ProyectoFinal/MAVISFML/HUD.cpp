#include "HUD.h"

HUD::HUD() {
    // Cargar la fuente (asegúrate de tener un archivo de fuente .ttf)
    if (!font.loadFromFile("../../res/OpenSans-Regular.ttf")) {
        // Manejar error
    }

    // Inicializar textos
    initializeText(livesText, font, 24, sf::Color::White, sf::Vector2f(10.f, 10.f));
    initializeText(scoreText, font, 24, sf::Color::White, sf::Vector2f(10.f, 40.f));
}

void HUD::initializeText(sf::Text& text, const sf::Font& font, unsigned int size, const sf::Color& color, const sf::Vector2f& position) {
    text.setFont(font);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(position);
}

void HUD::update(int lives, int score) {
    // Actualizar los textos con el puntaje y las vidas actuales
    livesText.setString("Lives: " + std::to_string(lives));
    scoreText.setString("Score: " + std::to_string(score));
}

void HUD::draw(sf::RenderWindow& window) {
    window.draw(livesText);
    window.draw(scoreText);
}