#pragma once

#include "Includes.h"

class GameManager
{
public:
    GameManager(sf::RenderWindow* app);
    void Start();
    void HandleEvents();
    void Update();

private:
    sf::RenderWindow* App;

    // Control de tiempo
    sf::Clock updateClock;   // Para actualizaciones cada 5 segundos
    sf::Clock gameTimeClock; // Para medir el tiempo total de juego
};

