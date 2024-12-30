#include "GameManager.h"

GameManager::GameManager(sf::RenderWindow* app) : App(app), lives(3), score(0), enemyCount(50), innocentCount(50), elapsedTime(0)
{
	App->setMouseCursorVisible(false); // Ocultar el cursor del mouse

	// Pew pew
	if (!shotBuffer.loadFromFile("../Recursos/Assets/GUNAuto_Shot beretta m12 9 mm (ID 0437)_BSB.ogg"))
	{
		// Si el sonido no se carga correctamente
		std::cerr << "Error al cargar el sonido de disparo" << std::endl;
	}
	shotSound.setVolume(100);
	shotSound.setLoop(false);
	shotSound.setBuffer(shotBuffer);

	// Cargar el fondo
	if (!BackgroundTexture.loadFromFile("../Recursos/Assets/bg_hud.png"))
	{
		throw std::runtime_error("Failed to load background texture.");
	}
	BackgroundSprite.setTexture(BackgroundTexture);

	// Crear la mira (crosshair). Tomada de mi propia actividad 6 de la unidad 4
	Crosshair crosshair();

	// Cargar texturas para personajes
	if (!enemyTexture.loadFromFile("../Recursos/Assets/Enemy.png"))
	{
		throw std::runtime_error("Error cargando textura de enemigo");
	}

	if (!innocentTexture.loadFromFile("../Recursos/Assets/Innocent.png"))
	{
		throw std::runtime_error("Error cargando textura de inocente");
	}

	// Cargar la textura para el agujero de bala
	if (!bulletHoleTexture.loadFromFile("../Recursos/Assets/bullet_hole.png"))
	{
		throw std::runtime_error("Error cargando textura de agujero de bala");
	}

	// Cargar fuente
	if (!font.loadFromFile("../Recursos/Fonts/west.ttf"))
	{
		throw std::runtime_error("Failed to load font.");
	}
	
	// Textos
	scoreText.setFont(font);
	scoreText.setCharacterSize(72);
	scoreText.setFillColor(sf::Color::Red);
	scoreText.setPosition(100, 850);

	livesText.setFont(font);
	livesText.setCharacterSize(72);
	livesText.setFillColor(sf::Color::Red);
	livesText.setPosition(500, 850);

	timeText.setFont(font);
	timeText.setCharacterSize(72);
	timeText.setFillColor(sf::Color::Red);
	timeText.setPosition(800, 850);

	// Generar personajes
	GenerateCharacters();
}

void GameManager::Start()
{
	// Mostrar pantalla de introducción
	ShowIntroScreen();

	// Reiniciar el reloj del tiempo total y de actualización
	gameTimeClock.restart();
	updateClock.restart();

	// Comenzar el ciclo del juego
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

			//// Escribir las coordenadas del click en la consola
			//std::cout << "Clic detectado en: ("
			//	<< event.mouseButton.x << ", "
			//	<< event.mouseButton.y << ")"
			//	<< std::endl;

			// Generar un desplazamiento aleatorio entre -30 y 30 para X y Y
			float offsetX = (std::rand() % 61 - 30);  // Aparentemente el algoritmo es rand%(max-min +1): https://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored
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

	// Actualizar posición de la mira
	crosshair.updatePosition(*App);

	// Dibujar la mira
	crosshair.draw(*App);

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
	// Crear el texto de la victoria
	sf::Text winText;
	winText.setFont(font);
	winText.setCharacterSize(150);  // Tamaño de fuente grande
	winText.setFillColor(sf::Color::Green);  // Verde para la victoria
	winText.setString("GANASTE!");

	// Centrar el texto
	sf::FloatRect textBounds = winText.getLocalBounds();
	winText.setOrigin(textBounds.width / 2, textBounds.height / 2);
	winText.setPosition(App->getSize().x / 2, App->getSize().y / 3);

	// Crear el texto del puntaje final
	sf::Text finalScoreText;
	finalScoreText.setFont(font);
	finalScoreText.setCharacterSize(80);
	finalScoreText.setFillColor(sf::Color::Green);
	finalScoreText.setString("Puntaje Final: " + std::to_string(score));

	// Centrar el texto en la pantalla
	sf::FloatRect scoreBounds = finalScoreText.getLocalBounds();
	finalScoreText.setOrigin(scoreBounds.width / 2, scoreBounds.height / 2);
	finalScoreText.setPosition(App->getSize().x / 2, App->getSize().y / 2);

	App->clear();  // Limpiar la ventana
	App->draw(winText);
	App->draw(finalScoreText);  // Mostrar el puntaje final
	App->display();  // Mostrar la ventana con los textos

	// Esperar 5 segundos y después de cerrar la ventana
	sf::sleep(sf::seconds(5)); // Esperar 5 segundos antes de cerrar la ventana
	App->close(); // Cerrar la ventana después de mostrar el mensaje
}

void GameManager::ShowLoseScreen()
{
	// Crear el texto de la derrota
	sf::Text loseText;
	loseText.setFont(font);
	loseText.setCharacterSize(150);
	loseText.setFillColor(sf::Color::Red); // Rojo para la derrota
	loseText.setString("PERDISTE!");

	sf::FloatRect textBounds = loseText.getLocalBounds();
	loseText.setOrigin(textBounds.width / 2, textBounds.height / 2);
	loseText.setPosition(App->getSize().x / 2, App->getSize().y / 3);

	sf::Text finalScoreText;
	finalScoreText.setFont(font);
	finalScoreText.setCharacterSize(80);
	finalScoreText.setFillColor(sf::Color::Red);
	finalScoreText.setString("Puntaje Final: " + std::to_string(score));

	sf::FloatRect scoreBounds = finalScoreText.getLocalBounds();
	finalScoreText.setOrigin(scoreBounds.width / 2, scoreBounds.height / 2);
	finalScoreText.setPosition(App->getSize().x / 2, App->getSize().y / 2);

	App->clear();
	App->draw(loseText);
	App->draw(finalScoreText);
	App->display();

	//// Esperar antes de cerrar la ventana
	sf::sleep(sf::seconds(5));  // Esperar 5 segundos antes de cerrar la ventana
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
	// No quería que los personajes aparezcan en lugares 100% random, por ejemplo aparecían volando en el cielo.
	// Entonces hice que la consola escriba las coordenadas donde se clickea y usé el propio juego para clickear las posiciones posibles que yo sí quería admitir.
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

	// inicializar el randomizador
	std::srand(static_cast<unsigned int>(std::time(0)));

	// Generar enemigos
	for (int i = 0; i < enemyCount; ++i)
	{
		// Generar un índice aleatorio para elegir alguna de las posiciones posibles (del vector de posiciones)
		int randomIndex = std::rand() % PossibleCoordinates.size();
		sf::Vector2f position = PossibleCoordinates[randomIndex];

		// Añadir el enemigo a la lista
		// emplace_back llama directamente al constructor con los parámetros dados, y así uno se evita hacer un puntero a una nueva instancia y después tener que limpiarlo
		enemies.emplace_back(enemyTexture, position.x, position.y, 3.f);
	}

	// Generar inocentes (misma lógica)
	for (int i = 0; i < innocentCount; ++i)
	{
		int randomIndex = std::rand() % PossibleCoordinates.size();
		sf::Vector2f position = PossibleCoordinates[randomIndex];
		innocents.emplace_back(innocentTexture, position.x, position.y, 3.f);
	}
}

void GameManager::UpdateAndDrawCharacters()
{
	// Dibujar al primer enemigo
	if (!enemies.empty())
	{
		// Obtener el enemigo actual de la lista de enemigos que tenemos que ir reduciendo
		Enemy& enemy = enemies.front();

		// Calcular el factor de escala cuadrático basado en la posición Y del enemigo
		// la idea era que cuanto más "lejos" (más arriba) estuviera el personaje, más chiquito se vea.
		float scaleFactor = 1.0f + 4.0f * std::pow((enemy.getPosition().y / App->getSize().y), 2);  // Exponente cuadrático para mayor efecto. 100% a ojo.

		// Aplicar la escala al sprite del enemigo
		enemy.getSprite().setScale(scaleFactor, scaleFactor);

		// Dibujar al enemigo con la escala aplicada
		App->draw(enemy);
	}

	// Dibujar al primer inocente de la lista. Ojalá sobrevivan todos. (misma lógica que con enemigos).
	if (!innocents.empty())
	{
		Innocent& innocent = innocents.front();
		float scaleFactor = 1.0f + 4.0f * std::pow((innocent.getPosition().y / App->getSize().y), 2);
		innocent.getSprite().setScale(scaleFactor, scaleFactor);
		App->draw(innocent);
	}

	if (lives <= 0)
	{
		ShowLoseScreen(); // Perdimos
	}
}

void GameManager::UpdateText()
{
	// Actualizar el puntaje.
	// Nota: Este "truco" de ostringstream << string fue generado con IA porque no me funcionaba que el puntaje y el tiempo y las vidas se vayan actualizando "en vivo".
	// No termino de tener claro por qué pero parece que haciendo un ostringstream le podemos "volcar" strings tal como hacemos con std::cout y sí se muestra bien.
	// Pensé en hacer scoreText.setString("Puntaje: " + score) y no lo pude hacer andar. Así funciona así que lo acepté.
	std::ostringstream scoreStream;
	scoreStream << "Puntaje: " << score;
	scoreText.setString(scoreStream.str());

	// Vidas
	std::ostringstream livesStream;
	livesStream << "Vidas: " << lives;
	livesText.setString(livesStream.str());

	// Tiempo
	std::ostringstream timeStream;
	timeStream << "Tiempo: " << static_cast<int>(gameTimeClock.getElapsedTime().asSeconds());
	timeText.setString(timeStream.str());
}

void GameManager::CheckClick(const sf::Vector2f& clickPosition)
{
	// Verificar si le dimos al enemigo
	if (!enemies.empty() && enemies.front().getGlobalBounds().contains(clickPosition))
	{
		// Sumamos puntos y eliminamos al primer enemigo (siempre dibujamos y matamos al primero del vector de enemigos).
		score += 10;
		enemies.erase(enemies.begin());
	}
	// Verificar si le digmos a un inocente
	else if (!innocents.empty() && innocents.front().getGlobalBounds().contains(clickPosition))
	{
		// Matar a un inocente resta mucho más de lo que suma matar a un enemigo, es una falta grave.
		// y desde luego que perdemos una vida tambié.n
		score -= 50;
		lives -= 1;
		innocents.erase(innocents.begin());
	}

	// Crear un nuevo agujero de bala centrado en la posición del click
	// si bien se recibe clickPosition y se pasa directamente como viene, fue pre-randomizado para dar la sensación de impresición de cada disparo y que den ganas de disparar muchísimo.
	// a este efecto se le suma el sonido de disparo, la idea es que se sienta satisfactorio disparar a lo bestia cuando aparece un enemigo.
	BulletHole bulletHole(bulletHoleTexture, clickPosition);
	bulletHoles.push_back(bulletHole);  // Agregar el agujero de bala al contenedor
}

void GameManager::ShowIntroScreen()
{
	// Textos del menú introductorio. Las tildes no funcionan.
	
	sf::Text titleText;
	titleText.setFont(font);
	titleText.setCharacterSize(75);
	titleText.setFillColor(sf::Color::White);
	titleText.setString("EL SHERIFF");

	sf::Text introText1;
	introText1.setFont(font);
	introText1.setCharacterSize(35);  // Tamaño de fuente
	introText1.setFillColor(sf::Color::White);  // Color blanco
	introText1.setString("Bienvenido, sheriff. Los bandidos han escapado y andan sueltos en nuestro pueblo lejano...");

	sf::Text introText2;
	introText2.setFont(font);
	introText2.setCharacterSize(35);
	introText2.setFillColor(sf::Color::White);
	introText2.setString("Pero cuidado! hay muchos ciudadanos inocentes caminando!");

	sf::Text introText3;
	introText3.setFont(font);
	introText3.setCharacterSize(35);
	introText3.setFillColor(sf::Color::White);
	introText3.setString("Solo debes dispararle a los bandidos.");

	sf::Text introText4;
	introText4.setFont(font);
	introText4.setCharacterSize(50);
	introText4.setFillColor(sf::Color::Red);
	introText4.setString("Haz click para comenzar el juego... El tiempo corre!");

	titleText.setPosition(App->getSize().x / 2 - titleText.getLocalBounds().width / 2, App->getSize().y / 3); // posiciones encontradas experimentando
	introText1.setPosition(App->getSize().x / 2 - introText1.getLocalBounds().width / 2, App->getSize().y / 3 + +100 + 0);
	introText2.setPosition(App->getSize().x / 2 - introText2.getLocalBounds().width / 2, App->getSize().y / 3 + +100 + 60);
	introText3.setPosition(App->getSize().x / 2 - introText3.getLocalBounds().width / 2, App->getSize().y / 3 + +100 + 120);
	introText4.setPosition(App->getSize().x / 2 - introText4.getLocalBounds().width / 2, App->getSize().y / 3 + +100 + 200);

	// Fondo negro para la pantalla de entrada
	sf::RectangleShape background(sf::Vector2f(App->getSize().x, App->getSize().y));
	background.setFillColor(sf::Color(0, 0, 0, 180));

	// Mostrar la pantalla de introducción
	App->clear();
	App->draw(background);
	App->draw(titleText);
	App->draw(introText1);
	App->draw(introText2);
	App->draw(introText3);
	App->draw(introText4);
	App->display();

	// Esperar hasta que el jugador haga click
	bool clicked = false;
	while (!clicked && App->isOpen())
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
				clicked = true;
			}
		}
	}
}