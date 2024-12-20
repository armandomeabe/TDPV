#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "BaseObject.h"

class Game {
public:
    Game(int width, int height);
    void Run();

private:
    void HandleEvents();
    void Update(float dt);
    void Render();
    void SpawnEnemy();
    void HandleCollisions();

    sf::Font font;
    sf::RenderWindow window;
    std::vector<std::unique_ptr<BaseObject>> enemies;
    std::vector<std::unique_ptr<BaseObject>> bullets;
    float spawnTimer;
    float spawnInterval;
    int score;
};
