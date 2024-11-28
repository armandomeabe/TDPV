#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <stdexcept>
#include <sstream>
#include "Enemy.h"
#include "Innocent.h"

class GameManager
{
public:
    GameManager(sf::RenderWindow* app);

    void Start();

private:
    sf::Text timeText;  // Texto para mostrar el tiempo
    sf::Clock timer;    // Reloj para medir el tiempo

    sf::RenderWindow* App;
    sf::Texture BackgroundTexture;
    sf::Sprite BackgroundSprite;

    sf::Texture enemyTexture;
    sf::Texture innocentTexture;

    sf::Font font;
    sf::Text scoreText;
    sf::Text livesText;

    int score;
    int lives;

    std::vector<Enemy> enemies;
    std::vector<Innocent> innocents;

    void HandleEvents();
    void Update();
    void ScaleBackground();
    void GenerateCharacters();
    void UpdateAndDrawCharacters();
    void UpdateText();
    void CheckClick(const sf::Vector2f& clickPosition);
};

#endif // GAMEMANAGER_H
