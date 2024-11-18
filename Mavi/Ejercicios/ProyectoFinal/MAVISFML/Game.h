#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Crosshair.h"
#include "HUD.h"
#include "Menu.h"
#include "Enemy.h"       // Asumimos que tienes estas clases
#include "Innocent.h"

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    sf::Texture crosshairTexture;
    sf::Texture enemyTexture;
    sf::Texture innocentTexture;
    Crosshair crosshair;
    HUD hud;
    Menu menu;
    std::vector<Enemy> enemies;     // Lista de enemigos
    std::vector<Innocent> innocents; // Lista de inocentes

    void processEvents();
    void update(sf::Time deltaTime);
    void render();

    bool isMenuActive;
    int lives;
    int score;

    void initializeGameObjects();
};

#endif