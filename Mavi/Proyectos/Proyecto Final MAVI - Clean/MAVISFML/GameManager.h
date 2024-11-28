#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include "Enemy.h"
#include "Innocent.h"

class GameManager
{
public:
    // Constructor
    GameManager(sf::RenderWindow* app);

    // Iniciar el juego
    void Start();

private:
    sf::RenderWindow* App;             // Ventana de renderizado
    sf::Texture BackgroundTexture;     // Textura para el fondo
    sf::Sprite BackgroundSprite;       // Sprite para el fondo

    std::vector<Enemy> enemies;        // Vector de enemigos
    std::vector<Innocent> innocents;   // Vector de inocentes

    sf::Texture enemyTexture;          // Textura para los enemigos
    sf::Texture innocentTexture;       // Textura para los inocentes

    sf::Clock timer;                   // Reloj para controlar el tiempo transcurrido

    // Manejar los eventos (teclado, mouse, etc.)
    void HandleEvents();

    // Actualizar el juego
    void Update();

    // Escalar el fondo para ocupar toda la ventana
    void ScaleBackground();

    // Generar personajes
    void GenerateCharacters();

    // Actualizar y dibujar personajes
    void UpdateAndDrawCharacters();
};

#endif // GAMEMANAGER_H
