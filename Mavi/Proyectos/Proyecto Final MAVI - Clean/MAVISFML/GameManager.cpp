#include "Includes.h"
#include "GameManager.h"

GameManager::GameManager(sf::RenderWindow* app) : App(app), lives(3), score(0), enemyCount(50), innocentCount(50)
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
    gameTimeClock.restart();  // Reiniciar el reloj del tiempo total
    updateClock.restart();    // Reiniciar el reloj de actualización
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

            // Escribir las coordenadas del clic en la consola
            std::cout << "Clic detectado en: ("
                << event.mouseButton.x << ", "
                << event.mouseButton.y << ")"
                << std::endl;

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

void GameManager::GenerateCharacters()
{
    // Coordenadas predefinidas
    PossibleCoordinates = {
        {971, 744}, {1053, 729}, {1104, 675}, {1102, 593}, {917, 588},
        {838, 609}, {701, 644}, {636, 650}, {415, 653}, {295, 653},
        {262, 629}, {251, 611}, {381, 570}, {413, 569}, {524, 583},
        {578, 579}, {674, 586}, {739, 585}, {792, 575}, {807, 553},
        {777, 522}, {654, 523}, {637, 525}, {573, 528}, {532, 531},
        {1002, 194}, {1031, 174}, {1056, 159}, {1090, 139}, {1115, 121},
        {949, 267}, {242, 227}, {274, 243}, {310, 268}, {345, 269},
        {394, 269}, {194, 151}
    };

    // Inicializar el generador de números aleatorios
    std::srand(static_cast<unsigned int>(std::time(0)));

    // Generar 4 enemigos
    for (int i = 0; i < enemyCount && !PossibleCoordinates.empty(); ++i)
    {
        // Generar un índice aleatorio
        int randomIndex = std::rand() % PossibleCoordinates.size();
        sf::Vector2f position = PossibleCoordinates[randomIndex];

        // Añadir el enemigo a la lista
        enemies.emplace_back(enemyTexture, position.x, position.y, 3.f);
    }

    // Generar 4 inocentes
    for (int i = 0; i < innocentCount && !PossibleCoordinates.empty(); ++i)
    {
        // Generar un índice aleatorio
        int randomIndex = std::rand() % PossibleCoordinates.size();
        sf::Vector2f position = PossibleCoordinates[randomIndex];

        // Añadir el inocente a la lista
        innocents.emplace_back(innocentTexture, position.x, position.y, 3.f);
    }
}

void GameManager::UpdateAndDrawCharacters()
{
    if (updateClock.getElapsedTime().asSeconds() >= 5.f)
    {
        // Eliminar un enemigo si existe
        if (!enemies.empty())
        {
            enemies.erase(enemies.begin());
            score -= 10;  // Restar puntos por no disparar al enemigo
            lives -= 1;   // Perder una vida
        }

        // Eliminar un inocente si existe
        if (!innocents.empty())
        {
            innocents.erase(innocents.begin());
        }

        // Generar un nuevo enemigo y un nuevo inocente
        if (lives > 0)  // Solo generar si quedan vidas
        {
            GenerateCharacter(true);  // Generar un nuevo enemigo
            GenerateCharacter(false); // Generar un nuevo inocente
        }

        updateClock.restart();  // Reiniciar el reloj de actualización
    }

    // Dibujar al primer enemigo
    if (!enemies.empty())
    {
        // Obtener el enemigo actual
        Enemy& enemy = enemies.front();

        // Calcular el factor de escala cuadrático basado en la posición Y del enemigo
        float scaleFactor = 1.0f + 4.0f * std::pow((enemy.getPosition().y / App->getSize().y), 2);  // Exponente cuadrático para mayor efecto

        // Aplicar la escala al sprite del enemigo
        enemy.getSprite().setScale(scaleFactor, scaleFactor);

        // Dibujar al enemigo con la escala aplicada
        App->draw(enemy);
    }

    // Dibujar al primer inocente
    if (!innocents.empty())
    {
        // Obtener el inocente actual
        Innocent& innocent = innocents.front();

        // Calcular el factor de escala cuadrático basado en la posición Y del inocente
        float scaleFactor = 1.0f + 4.0f * std::pow((innocent.getPosition().y / App->getSize().y), 2);  // Exponente cuadrático para mayor efecto

        // Aplicar la escala al sprite del inocente
        innocent.getSprite().setScale(scaleFactor, scaleFactor);

        // Dibujar al inocente con la escala aplicada
        App->draw(innocent);
    }

    // Si las vidas son 0, mostrar el mensaje de "¡PERDISTE!"
    if (lives <= 0)
    {
        // Crear el texto de "¡PERDISTE!"
        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setCharacterSize(150);  // Tamaño de fuente grande
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setString("PERDISTE!");

        // Centrar el texto en la pantalla
        sf::FloatRect textBounds = gameOverText.getLocalBounds();
        gameOverText.setOrigin(textBounds.width / 2, textBounds.height / 2);
        gameOverText.setPosition(App->getSize().x / 2, App->getSize().y / 3);

        // Crear el texto del puntaje final
        sf::Text finalScoreText;
        finalScoreText.setFont(font);
        finalScoreText.setCharacterSize(80);  // Tamaño de fuente para el puntaje
        finalScoreText.setFillColor(sf::Color::Red);
        finalScoreText.setString("Puntaje Final: " + std::to_string(score));

        // Centrar el texto de puntaje en la pantalla
        sf::FloatRect scoreBounds = finalScoreText.getLocalBounds();
        finalScoreText.setOrigin(scoreBounds.width / 2, scoreBounds.height / 2);
        finalScoreText.setPosition(App->getSize().x / 2, App->getSize().y / 2);

        // Dibujar el texto de "¡PERDISTE!" y el puntaje final
        App->clear();  // Limpiar la ventana
        App->draw(gameOverText);
        App->draw(finalScoreText);  // Mostrar el puntaje final
        App->display();  // Mostrar la ventana con los textos

        // Evitar que el juego continúe actualizándose
        // La ventana se mantendrá abierta mostrando el mensaje
        sf::sleep(sf::seconds(3));  // Esperar 3 segundos antes de cerrar la ventana (puedes ajustar este tiempo)
        App->close();  // Cerrar la ventana después de mostrar el mensaje
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

    // Actualizar el tiempo total del juego
    std::ostringstream timeStream;
    timeStream << "Tiempo: " << static_cast<int>(gameTimeClock.getElapsedTime().asSeconds());
    timeText.setString(timeStream.str());
}

void GameManager::CheckClick(const sf::Vector2f& clickPosition)
{
    // Verificar si se hace clic en el primer enemigo
    if (!enemies.empty() && enemies.front().getGlobalBounds().contains(clickPosition))
    {
        score += 10;
        enemies.erase(enemies.begin());
        updateClock.restart();  // Reiniciar el reloj de actualización
    }
    // Verificar si se hace clic en el primer inocente
    // este 'else' es intencional: Si justo un enemigo estaba superpuesto con un inocente, muere el enemigo y no el inocente. To serve and protect!
    else if (!innocents.empty() && innocents.front().getGlobalBounds().contains(clickPosition))
    {
        score -= 50;
        lives -= 1;
        innocents.erase(innocents.begin());
        updateClock.restart();  // Reiniciar el reloj de actualización
    }
}

void GameManager::GenerateCharacter(bool isEnemy)
{
    if (!PossibleCoordinates.empty())
    {
        // Seleccionar la última posición disponible de las coordenadas posibles
        sf::Vector2f position = PossibleCoordinates.back();
        PossibleCoordinates.pop_back(); // Eliminar la posición usada

        if (isEnemy)
        {
            // Crear un enemigo en la posición seleccionada
            enemies.emplace_back(enemyTexture, position.x, position.y, 3.f);
        }
        else
        {
            // Crear un inocente en la posición seleccionada
            innocents.emplace_back(innocentTexture, position.x, position.y, 3.f);
        }
    }
}
