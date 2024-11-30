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
#include "BulletHole.h"  // Incluir la clase BulletHole


class GameManager
{
public:
    GameManager(sf::RenderWindow* app);
    void Start();
    void ShowWinScreen();
    void ShowLoseScreen();
private:
    int enemyCount;
    int innocentCount;

    sf::RenderWindow* App;

    float elapsedTime; // Inicialización a un valor imposible (antes del primer segundo)

    // Sonidos
    sf::SoundBuffer shotBuffer;
    sf::Sound shotSound;

    // Texturas y sprites
    sf::Texture BackgroundTexture;
    sf::Sprite BackgroundSprite;
    sf::Texture enemyTexture;
    sf::Texture innocentTexture;
    sf::Texture bulletHoleTexture;  // Textura para el agujero de bala

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

    // Listas de personajes y otros
    std::vector<Enemy> enemies;
    std::vector<Innocent> innocents;
    std::vector<BulletHole> bulletHoles; // Contenedor de los agujeros de bala

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
