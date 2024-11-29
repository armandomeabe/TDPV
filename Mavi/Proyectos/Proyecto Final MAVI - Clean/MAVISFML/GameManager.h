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
    int enemyCount;
    int innocentCount;

    sf::RenderWindow* App;

    // Texturas y sprites
    sf::Texture BackgroundTexture;
    sf::Sprite BackgroundSprite;
    sf::Texture enemyTexture;
    sf::Texture innocentTexture;

    // Textos y fuentes
    sf::Font font;
    sf::Text scoreText;
    sf::Text livesText;
    sf::Text timeText;

    // Variables del juego
    int score;
    int lives;

    // Control de tiempo
    sf::Clock timer;         // Para intervalos entre eventos
    sf::Clock updateClock;   // Para actualizaciones dinámicas (cada 5 segundos)
    sf::Clock gameTimeClock; // Para medir el tiempo total de juego

    // Coordenadas posibles para generar personajes
    std::vector<sf::Vector2f> PossibleCoordinates;

    // Listas de personajes
    std::vector<Enemy> enemies;
    std::vector<Innocent> innocents;

    // Métodos principales
    void HandleEvents();
    void Update();
    void ScaleBackground();
    void GenerateCharacters();           // Mantener este si necesitas el método general
    void GenerateCharacter(bool isEnemy); // Método para generar personajes individuales
    void UpdateAndDrawCharacters();
    void UpdateText();
    void CheckClick(const sf::Vector2f& clickPosition);
};

#endif // GAMEMANAGER_H
