#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Bullet.h"

Game::Game(int width, int height)
	: window(sf::VideoMode(width, height), "Disparale a los objetos"), spawnTimer(0), spawnInterval(0.5f), score(0) {
	srand(static_cast<unsigned>(time(nullptr))); // Semilla para números aleatorios
	font.loadFromFile("../../Res/Fonts/Montserrat-SemiBold.ttf");
}

void Game::Run() {
	sf::Clock clock;
	while (window.isOpen()) {
		float dt = clock.restart().asSeconds();
		HandleEvents();
		Update(dt);
		Render();
	}
}

void Game::HandleEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		// Disparo al presionar el botón izquierdo del mouse
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			bullets.push_back(std::make_unique<Bullet>(5.0f, sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))));
			(*bullets.back()).SetPosition(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)));

		}
	}
}


void Game::Update(float dt) {
	spawnTimer += dt;

	// Spawn de nuevos enemigos
	if (spawnTimer >= spawnInterval) {
		SpawnEnemy();
		spawnTimer = 0;
	}

	// Actualizar enemigos
	for (auto& enemy : enemies) {
		if (enemy) {
			enemy->Update(dt);
			sf::Vector2f pos = enemy->GetPosition();
			if (pos.y > window.getSize().y || pos.x > window.getSize().x || pos.x < -100.0f) {
				enemy.reset();
			}
		}
	}
	enemies.erase(std::remove(enemies.begin(), enemies.end(), nullptr), enemies.end());

	// Actualizar balas
	for (auto& bullet : bullets) {
		bullet->Update(dt);
	}

	// Este codigo con "remove_if" fue generado por IA y me sirvio para aprender que std tiene mucho mas de lo que siempre use
	// Sirve para crear punteros y hacer remove_if es decir desde un iterator en el principio y uno en el final (para macarle el rango)
	// por cada elemento que cumpla la condicion, lo elimina. Asi puedo modificar el mismo vector que estoy tratando de iterar.
	bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
		[](const std::unique_ptr<Bullet>& bullet) {
			return bullet->Obsolete();
		}),
		bullets.end());

	// Manejo de colisiones entre balas y enemigos
	HandleCollisions();
}

void Game::Render() {
	window.clear();

	// Dibujar los enemigos
	for (const auto& enemy : enemies) {
		if (enemy) {
			enemy->Draw(&window);
		}
	}

	// Dibujar balas
	for (const auto& bullet : bullets) {
		if (bullet)
		{
			bullet->Draw(&window);
		}
		//window.draw(bullet.get().get);

		//std::cout << (*bullet).GetPosition().x << std::endl;
	}

	sf::Text scoreText("Puntaje: " + std::to_string(score), font, 24);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(10, 10);
	window.draw(scoreText);

	window.display();
}

void Game::SpawnEnemy() {
	// Crear un enemigo con una textura específica
	auto enemy = std::make_unique<BaseObject>("../../Res/ufo.png");

	// Posición inicial aleatoria (arriba o a los lados de la ventana)
	sf::Vector2f position;
	if (rand() % 2 == 0) {
		// Desde arriba
		position = sf::Vector2f(rand() % window.getSize().x, 0);
	}
	else {
		// Desde los lados
		position = sf::Vector2f((rand() % 2 == 0) ? 0 : window.getSize().x, rand() % window.getSize().y);
	}

	// Configuración de velocidad y aceleración para MRUV
	sf::Vector2f velocity(rand() % 200 - 100, rand() % 200 - 100); // Velocidad inicial aleatoria
	sf::Vector2f acceleration(0, 50); // Aceleración constante hacia abajo

	enemy->SetPosition(position);
	enemy->SetVelocity(velocity);
	enemy->SetAcceleration(acceleration);
	enemy->SetScale(0.1f);

	enemies.push_back(std::move(enemy));
}

void Game::HandleCollisions() {
	for (auto& bullet : bullets) {
		for (auto& enemy : enemies) {
			if (enemy) { // Solo verificar colisiones si el puntero enemigo es válido
				sf::FloatRect bulletBounds = bullet->getGlobalBounds();

				sf::Vector2f enemySize(
					static_cast<float>(enemy->GetTextureSize().x),
					static_cast<float>(enemy->GetTextureSize().y)
				);

				sf::FloatRect enemyBounds(
					enemy->GetPosition().x,
					enemy->GetPosition().y,
					enemySize.x * enemy->GetScale(),
					enemySize.y * enemy->GetScale()
				);

				if (bulletBounds.intersects(enemyBounds)) {
					// Incrementar el puntaje
					score += 10;

					// Marcar bala como obsoleta
					//bullet->SetPosition(sf::Vector2f(-100.0f, -100.0f)); // Alejar la bala de la pantalla
					enemy.reset(); // Eliminar enemigo

					// Si impacta con un ovni, la bala ya se gasta asi que es obsoleta
					bullet->SetManuallyObsolete();
				}
			}
		}
	}

	// Limpiar enemigos eliminados
	enemies.erase(std::remove(enemies.begin(), enemies.end(), nullptr), enemies.end());
}
