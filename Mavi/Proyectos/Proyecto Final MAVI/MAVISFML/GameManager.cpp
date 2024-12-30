#include "GameManager.h"

GameManager::GameManager(sf::RenderWindow* app) : App(app)
{
	App->setMouseCursorVisible(false); // Ocultar el cursor del mouse
}

void GameManager::Start()
{
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
			// en caso de click... etc.
		}
	}
}

void GameManager::Update()
{
	App->clear();
	
	// Logica aca...

	App->display();
}