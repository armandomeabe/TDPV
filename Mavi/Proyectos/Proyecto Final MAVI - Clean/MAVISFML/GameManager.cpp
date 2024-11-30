#include "Includes.h"
#include "GameManager.h"

GameManager::GameManager(sf::RenderWindow* app) : App(app), lives(3), score(0), enemyCount(50), innocentCount(50), elapsedTime(0)
{
	// Sonido de disparo
	if (!shotBuffer.loadFromFile("../Recursos/Assets/GUNAuto_Shot beretta m12 9 mm (ID 0437)_BSB.ogg"))
	{
		// Manejar error si el sonido no se carga correctamente
		std::cerr << "Error al cargar el sonido de disparo" << std::endl;
	}
	shotSound.setVolume(100); // Ajusta el volumen entre 0 y 100
	shotSound.setLoop(false); // No repetir el sonido, solo una vez
	shotSound.setBuffer(shotBuffer);  // Asignar el buffer al sonido

	// Cargar el fondo inicial
	if (!BackgroundTexture.loadFromFile("../Recursos/Assets/bg_hud.png"))
	{
		throw std::runtime_error("Failed to load background texture.");
	}
	BackgroundSprite.setTexture(BackgroundTexture);

	// Cargar texturas para personajes
	if (!enemyTexture.loadFromFile("../Recursos/Assets/Enemy.png"))
	{
		throw std::runtime_error("Failed to load Enemy texture.");
	}

	if (!innocentTexture.loadFromFile("../Recursos/Assets/Innocent.png"))
	{
		throw std::runtime_error("Failed to load Innocent texture.");
	}

	// Cargar la textura para el agujero de bala
	if (!bulletHoleTexture.loadFromFile("../Recursos/Assets/bullet_hole.png"))
	{
		throw std::runtime_error("Failed to load bullet hole texture.");
	}

	// Cargar fuente
	if (!font.loadFromFile("../Recursos/Fonts/west.ttf"))
	{
		throw std::runtime_error("Failed to load font.");
	}
	
	// Configurar textos
	scoreText.setFont(font);
	scoreText.setCharacterSize(72);
	scoreText.setFillColor(sf::Color::Red);
	scoreText.setPosition(100, 850);

	livesText.setFont(font);
	livesText.setCharacterSize(72);
	livesText.setFillColor(sf::Color::Red);
	livesText.setPosition(500, 850);

	// Configurar texto para el tiempo
	timeText.setFont(font);
	timeText.setCharacterSize(72);
	timeText.setFillColor(sf::Color::Red);
	timeText.setPosition(800, 850);

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
			shotSound.play();  // Reproducir el sonido del disparo

			// Escribir las coordenadas del clic en la consola
			std::cout << "Clic detectado en: ("
				<< event.mouseButton.x << ", "
				<< event.mouseButton.y << ")"
				<< std::endl;

			// Generar un desplazamiento aleatorio entre -30 y 30 para X y Y
			float offsetX = (std::rand() % 61 - 30);  // Rango entre -30 y 30 ¿por qué 61-30? ni la menor idea pero funciona: https://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored
			float offsetY = (std::rand() % 61 - 30);

			sf::Vector2f clickPosition(event.mouseButton.x + offsetX, event.mouseButton.y + offsetY);
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

	// Si todos los enemigos han sido eliminados, mostrar el mensaje de victoria
	if (enemies.empty())
	{
		ShowWinScreen();
	}

	// Cuánto tiempo pasó
	float deltaTime = updateClock.restart().asSeconds();

	// Actualizar los enemigos y los inocentes en caso de que ya hayan transcurrido 5 segundos
	auto& innocent = innocents.front(); // escribir "auto" es casi tanto trabajo como escribir el nombre de la variable, me encantaría que fuera var como C#
	innocent.Update(deltaTime);
	if (innocent.IsExpired())
	{
		innocents.erase(innocents.begin());
	}

	auto& enemy = enemies.front();
	enemy.Update(deltaTime);
	if (enemy.IsExpired())
	{
		enemies.erase(enemies.begin());
	}

	// Actualizar los agujeros de bala
	for (auto it = bulletHoles.begin(); it != bulletHoles.end();)
	{
		it->Update(deltaTime); // Actualizar el tiempo de vida del agujero de bala

		if (it->IsExpired())  // Si el agujero de bala ha expirado, eliminarlo
		{
			it = bulletHoles.erase(it);
		}
		else
		{
			++it;
		}
	}

	// Dibujar los agujeros de bala
	for (const auto& bulletHole : bulletHoles)
	{
		App->draw(bulletHole);
	}

	App->display();
}

void GameManager::ShowWinScreen()
{
	// Crear el texto de "¡GANASTE!"
	sf::Text winText;
	winText.setFont(font);
	winText.setCharacterSize(150);  // Tamaño de fuente grande
	winText.setFillColor(sf::Color::Green);  // Puedes cambiar el color
	winText.setString("GANASTE!");

	// Centrar el texto de "¡GANASTE!"
	sf::FloatRect textBounds = winText.getLocalBounds();
	winText.setOrigin(textBounds.width / 2, textBounds.height / 2);
	winText.setPosition(App->getSize().x / 2, App->getSize().y / 3);

	// Crear el texto del puntaje final
	sf::Text finalScoreText;
	finalScoreText.setFont(font);
	finalScoreText.setCharacterSize(80);  // Tamaño de fuente para el puntaje
	finalScoreText.setFillColor(sf::Color::Green);  // Color verde
	finalScoreText.setString("Puntaje Final: " + std::to_string(score));

	// Centrar el texto de puntaje en la pantalla
	sf::FloatRect scoreBounds = finalScoreText.getLocalBounds();
	finalScoreText.setOrigin(scoreBounds.width / 2, scoreBounds.height / 2);
	finalScoreText.setPosition(App->getSize().x / 2, App->getSize().y / 2);

	// Dibujar el texto de "¡GANASTE!" y el puntaje final
	App->clear();  // Limpiar la ventana
	App->draw(winText);
	App->draw(finalScoreText);  // Mostrar el puntaje final
	App->display();  // Mostrar la ventana con los textos

	// Esperar unos segundos antes de cerrar la ventana
	sf::sleep(sf::seconds(3));  // Esperar 3 segundos antes de cerrar la ventana
	App->close();  // Cerrar la ventana después de mostrar el mensaje
}

void GameManager::ShowLoseScreen()
{
	// Crear el texto de "¡PERDISTE!"
	sf::Text loseText;
	loseText.setFont(font);
	loseText.setCharacterSize(150);  // Tamaño de fuente grande
	loseText.setFillColor(sf::Color::Red);  // Color rojo
	loseText.setString("PERDISTE!");

	// Centrar el texto de "¡PERDISTE!"
	sf::FloatRect textBounds = loseText.getLocalBounds();
	loseText.setOrigin(textBounds.width / 2, textBounds.height / 2);
	loseText.setPosition(App->getSize().x / 2, App->getSize().y / 3);

	// Crear el texto del puntaje final
	sf::Text finalScoreText;
	finalScoreText.setFont(font);
	finalScoreText.setCharacterSize(80);  // Tamaño de fuente para el puntaje
	finalScoreText.setFillColor(sf::Color::Red);  // Color rojo
	finalScoreText.setString("Puntaje Final: " + std::to_string(score));

	// Centrar el texto de puntaje en la pantalla
	sf::FloatRect scoreBounds = finalScoreText.getLocalBounds();
	finalScoreText.setOrigin(scoreBounds.width / 2, scoreBounds.height / 2);
	finalScoreText.setPosition(App->getSize().x / 2, App->getSize().y / 2);

	// Dibujar el texto de "¡PERDISTE!" y el puntaje final
	App->clear();  // Limpiar la ventana
	App->draw(loseText);
	App->draw(finalScoreText);  // Mostrar el puntaje final
	App->display();  // Mostrar la ventana con los textos

	// Esperar unos segundos antes de cerrar la ventana
	sf::sleep(sf::seconds(3));  // Esperar 3 segundos antes de cerrar la ventana
	App->close();  // Cerrar la ventana después de mostrar el mensaje
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
		{971, 600}, {1053, 600}, {1104, 600}, {1102, 593}, {917, 588},
		{838, 600}, {701, 600}, {636, 600}, {415, 600}, {295, 600},
		{262, 600}, {251, 600}, {381, 570}, {413, 569}, {524, 583},
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

	if (lives <= 0)
	{
		ShowLoseScreen();  // Llamamos al método para mostrar la pantalla de derrota
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
	}
	// Verificar si se hace clic en el primer inocente
	else if (!innocents.empty() && innocents.front().getGlobalBounds().contains(clickPosition))
	{
		score -= 50;
		lives -= 1;
		innocents.erase(innocents.begin());
	}

	// Crear un nuevo agujero de bala centrado en la posición del clic
	BulletHole bulletHole(bulletHoleTexture, clickPosition);
	bulletHoles.push_back(bulletHole);  // Agregar el agujero de bala al contenedor
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
