#pragma once
#include <SFML/Graphics.hpp>
#include "BaseObject.h"

using namespace sf;

class Game {
public:
    Game(int width, int height);
    void Run();

private:
    RenderWindow window;
    BaseObject ball;
    float gravity;
    float bounceFactor;

    void ProcessEvents();
    void Update(float dt);
    void Render();
};
