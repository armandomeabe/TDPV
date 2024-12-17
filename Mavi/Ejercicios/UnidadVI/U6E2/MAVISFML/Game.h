#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "BaseObject.h"

class Game {
public:
    Game(float v0, float vFinal); // Constructor con velocidades inicial y final
    ~Game();

    void Loop(); //

private:
    void processEvents();
    void update(float dt);
    void render();

    sf::RenderWindow window;
    BaseObject* car;     // El auto será un BaseObject
    float currentSpeedX; // Velocidad actual en X
    float currentSpeedY; // Velocidad actual en Y
    float finalSpeed;    // Velocidad máxima permitida
    float accelerationX; // Aceleración en X
    float accelerationY; // Aceleración en Y

    sf::Clock clock; // Reloj para delta time
};

#endif // GAME_H
