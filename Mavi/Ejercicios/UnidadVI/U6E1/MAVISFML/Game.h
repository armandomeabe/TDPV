#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "BaseObject.h"

class Game {
public:
    Game(float v0, float vFinal); // Constructor con velocidades inicial y final
    ~Game();

    void Loop(); // loop principal

private:
    void processEvents();
    void update(float dt);
    void render();

    sf::RenderWindow window;
    BaseObject* car;     // El auto es un BaseObject
    float currentSpeed;  // Velocidad actual del auto
    float finalSpeed;    // Velocidad máxima permitida (la condicion de corte)

    sf::Clock clock; // Reloj para el dt
};

#endif // GAME_H
