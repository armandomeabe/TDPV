#include "GameManager.h"

GameManager::GameManager(sf::RenderWindow* app) : App(app), lives(3), score(0)
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

    // Cargar fuente
    if (!font.loadFromFile("../Recursos/Fonts/west.ttf"))
    {
        throw std::runtime_error("Failed to load font.");
    }

    // Configurar textos
    scoreText.setFont(font);
    scoreText.setCharacterSize(48);
    scoreText.setFillColor(sf::Color::Red);
    scoreText.setPosition(10, 5);

    livesText.setFont(font);
    livesText.setCharacterSize(48);
    livesText.setFillColor(sf::Color::Red);
    livesText.setPosition(10, 60);

    // Configurar texto para el tiempo
    timeText.setFont(font);
    timeText.setCharacterSize(48);
    timeText.setFillColor(sf::Color::Red);
    timeText.setPosition(10, 115);

    // Generar personajes
    GenerateCharacters();
}

void GameManager::Start()
{
    timer.restart();
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
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f clickPosition(event.mouseButton.x, event.mouseButton.y);
            CheckClick(clickPosition);
        }
    }
}

void GameManager::Update()
{
    App->clear();
    App->draw(BackgroundSprite);
    UpdateAndDrawCharacters();
    UpdateText();  // Actualizar los textos (puntaje, vidas y tiempo)
    App->draw(scoreText);
    App->draw(livesText);
    App->draw(timeText);  // Dibujar el tiempo
    App->display();
}

void GameManager::ScaleBackground()
{
    sf::Vector2u windowSize = App->getSize();
    sf::FloatRect spriteBounds = BackgroundSprite.getLocalBounds();
    float scaleX = static_cast<float>(windowSize.x) / spriteBounds.width;
    float scaleY = static_cast<float>(windowSize.y) / spriteBounds.height;
    BackgroundSprite.setScale(scaleX, scaleY);
}

void GameManager::GenerateCharacters() {
    sf::Vector2u windowSize = App->getSize();
    srand(static_cast<unsigned>(time(nullptr)));

    // Generar 4 enemigos e inocentes
    for (int i = 0; i < 50; ++i) {
        // Generar enemigos
        float x = static_cast<float>(rand() % windowSize.x);
        float y = static_cast<float>(rand() % windowSize.y);

        // Verificar si la posición del enemigo está dentro de los límites de la ventana
        if (x + enemyTexture.getSize().x * 3.f > windowSize.x) {
            x = windowSize.x - enemyTexture.getSize().x * 3.f;  // Ajustar posición X
        }
        if (y + enemyTexture.getSize().y * 3.f > windowSize.y) {
            y = windowSize.y - enemyTexture.getSize().y * 3.f;  // Ajustar posición Y
        }

        enemies.emplace_back(enemyTexture, x, y, 3.f);  // Crear el enemigo con su textura y escala

        // Generar inocentes
        x = static_cast<float>(rand() % windowSize.x);
        y = static_cast<float>(rand() % windowSize.y);

        // Verificar si la posición del inocente está dentro de los límites de la ventana
        if (x + innocentTexture.getSize().x * 3.f > windowSize.x) {
            x = windowSize.x - innocentTexture.getSize().x * 3.f;  // Ajustar posición X
        }
        if (y + innocentTexture.getSize().y * 3.f > windowSize.y) {
            y = windowSize.y - innocentTexture.getSize().y * 3.f;  // Ajustar posición Y
        }

        innocents.emplace_back(innocentTexture, x, y, 3.f);  // Crear el inocente con su textura y escala
    }
}

void GameManager::UpdateAndDrawCharacters()
{
    if (timer.getElapsedTime().asSeconds() >= 5.f)
    {
        if (!enemies.empty())
        {
            enemies.erase(enemies.begin());  // Eliminar el primer enemigo
            score -= 10;  // Restar puntos por no disparar al enemigo
            lives -= 1;   // Perder una vida
        }

        if (!innocents.empty())
        {
            innocents.erase(innocents.begin());  // Eliminar el primer inocente
        }

        timer.restart();
    }

    // Dibujar al primer enemigo
    if (!enemies.empty())
    {
        App->draw(enemies.front());
    }

    // Dibujar al primer inocente
    if (!innocents.empty())
    {
        App->draw(innocents.front());
    }

    if (lives < 0)
    {
        App->close();
    }
}

void GameManager::UpdateText()
{
    // Actualizar el puntaje
    std::ostringstream scoreStream;
    scoreStream << "Puntaje: " << score;
    scoreText.setString(scoreStream.str());

    // Actualizar las vidas
    std::ostringstream livesStream;
    livesStream << "Vidas: " << lives;
    livesText.setString(livesStream.str());

    // Actualizar el tiempo
    std::ostringstream timeStream;
    timeStream << "Tiempo: " << static_cast<int>(timer.getElapsedTime().asSeconds());
    timeText.setString(timeStream.str());
}

void GameManager::CheckClick(const sf::Vector2f& clickPosition)
{
    // Verificar si se hace clic en el primer enemigo
    if (!enemies.empty() && enemies.front().getGlobalBounds().contains(clickPosition))
    {
        score += 10;
        enemies.erase(enemies.begin());
    }
    // Verificar si se hace clic en el primer inocente
    else if (!innocents.empty() && innocents.front().getGlobalBounds().contains(clickPosition))
    {
        score -= 50;
        lives -= 1;
        innocents.erase(innocents.begin());
    }
}
