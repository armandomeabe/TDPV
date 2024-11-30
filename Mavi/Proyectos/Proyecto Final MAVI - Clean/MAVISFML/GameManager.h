#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <ctime>
#include <stdexcept>
#include <sstream>
#include "Enemy.h"
#include "Innocent.h"
#include "BulletHole.h"
#include "Crosshair.h"
#include "Includes.h"

class GameManager
{
public:
    GameManager(sf::RenderWindow* app);
    void Start();
    void ShowWinScreen();
    void ShowLoseScreen();
    void ShowIntroScreen();

private:
    int enemyCount;
    int innocentCount;

    Crosshair crosshair;

    sf::RenderWindow* App;

    float elapsedTime;

    // Sonidos
    sf::SoundBuffer shotBuffer;
    sf::Sound shotSound;

    // Texturas y sprites
    // conforme el proyecto fue creciendo me di cuenta que cada textura debería ser responsabilidad de su propia clase.
    // migré la textura de Crosshair a la clase misma. TO-DO: Hacer lo mismo con enemigos e inocentes.
    sf::Texture BackgroundTexture;
    sf::Sprite BackgroundSprite;
    sf::Texture enemyTexture;
    sf::Texture innocentTexture;
    sf::Texture bulletHoleTexture;

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
    sf::Clock updateClock;   // Para actualizaciones cada 5 segundos
    sf::Clock gameTimeClock; // Para medir el tiempo total de juego

    // Coordenadas posibles para generar personajes, es un vector de pares (x,y). TO-DO: Investigar tuplas.
    std::vector<sf::Vector2f> PossibleCoordinates;

    // Listas de personajes y otros
    std::vector<Enemy> enemies;
    std::vector<Innocent> innocents;
    std::vector<BulletHole> bulletHoles;

    // Métodos principales
    void HandleEvents();
    void Update();
    void ScaleBackground();
    void GenerateCharacters();
    void UpdateAndDrawCharacters();
    void UpdateText();
    void CheckClick(const sf::Vector2f& clickPosition);
};

#endif // GAMEMANAGER_H
