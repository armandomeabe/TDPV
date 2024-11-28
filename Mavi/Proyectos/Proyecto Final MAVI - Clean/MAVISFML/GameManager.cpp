#include "GameManager.h"

GameManager::GameManager(sf::RenderWindow* app) : App(app)
{
    // Cargar el fondo inicial
    if (!BackgroundTexture.loadFromFile("../Recursos/Assets/bg.jpg"))
    {
        throw std::runtime_error("Failed to load background texture.");
    }
    BackgroundSprite.setTexture(BackgroundTexture);

    // Escalar el fondo para que ocupe toda la ventana
    ScaleBackground();

    // Cargar texturas para personajes
    if (!enemyTexture.loadFromFile("../Recursos/Assets/Enemy.png"))
    {
        throw std::runtime_error("Failed to load Enemy texture.");
    }

    if (!innocentTexture.loadFromFile("../Recursos/Assets/Innocent.png"))
    {
        throw std::runtime_error("Failed to load Innocent texture.");
    }

    // Generar personajes
    GenerateCharacters();
}

void GameManager::Start()
{
    // Reiniciar el temporizador al iniciar
    timer.restart();

    // Bucle principal del juego
    while (App->isOpen())
    {
        HandleEvents();
        Update();
    }
}

void GameManager::HandleEvents()
{
    sf::Event event;
    while (App->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            App->close();
        }
    }
}

void GameManager::Update()
{
    App->clear();                 // Limpiar la pantalla
    App->draw(BackgroundSprite);  // Dibujar el fondo

    UpdateAndDrawCharacters();    // Dibujar y actualizar los personajes

    App->display();               // Mostrar en pantalla
}

void GameManager::ScaleBackground()
{
    sf::Vector2u windowSize = App->getSize();
    sf::FloatRect spriteBounds = BackgroundSprite.getLocalBounds();
    float scaleX = static_cast<float>(windowSize.x) / spriteBounds.width;
    float scaleY = static_cast<float>(windowSize.y) / spriteBounds.height;
    BackgroundSprite.setScale(scaleX, scaleY);
}

void GameManager::GenerateCharacters()
{
    sf::Vector2u windowSize = App->getSize();
    srand(static_cast<unsigned>(time(nullptr)));

    // Generar 4 enemigos
    for (int i = 0; i < 4; ++i)
    {
        float x = static_cast<float>(rand() % windowSize.x);
        float y = static_cast<float>(rand() % windowSize.y);
        enemies.emplace_back(x, y);
    }

    // Generar 4 inocentes
    for (int i = 0; i < 4; ++i)
    {
        float x = static_cast<float>(rand() % windowSize.x);
        float y = static_cast<float>(rand() % windowSize.y);
        innocents.emplace_back(x, y);
    }
}

void GameManager::UpdateAndDrawCharacters()
{
    // Verificar si han pasado 5 segundos
    if (timer.getElapsedTime().asSeconds() >= 5.f)
    {
        // Eliminar el primer enemigo si el vector no está vacío
        if (!enemies.empty())
        {
            enemies.erase(enemies.begin());
        }

        // Eliminar el primer inocente si el vector no está vacío
        if (!innocents.empty())
        {
            innocents.erase(innocents.begin());
        }

        // Reiniciar el temporizador
        timer.restart();
    }

    // Dibujar solo el primer enemigo
    if (!enemies.empty())
    {
        sf::Sprite sprite;
        sprite.setTexture(enemyTexture);
        sprite.setPosition(enemies.front().getX(), enemies.front().getY());
        App->draw(sprite);
    }

    // Dibujar solo el primer inocente
    if (!innocents.empty())
    {
        sf::Sprite sprite;
        sprite.setTexture(innocentTexture);
        sprite.setPosition(innocents.front().getX(), innocents.front().getY());
        App->draw(sprite);
    }
}
