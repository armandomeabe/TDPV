#include "Game.h"
#include "Crosshair.h"
#include <iostream>
#include <memory>

Game::Game()
    : window(sf::VideoMode(800, 600), "Wild Armand"),
    menu(window.getSize().x, window.getSize().y),
    isMenuActive(true),
    lives(3),
    score(0),
    crosshair("../../res/crosshair.png")
{
    window.setMouseCursorVisible(false); // esconder el mouse
    
    if (!enemyTexture.loadFromFile("../../res/enemy.png")) {
        std::cerr << "Error al cargar la textura del enemigo" << std::endl;
        return;
    }
    if (!innocentTexture.loadFromFile("../../res/innocent.png")) {
        std::cerr << "Error al cargar la textura del inocente" << std::endl;
        return;
    }
    initializeGameObjects();
}

void Game::initializeGameObjects()
{
    enemies.clear();
    innocents.clear();
    for (int i = 0; i < 4; ++i) {
        /* La función emplace_back es un miembro de la clase std::vector en la biblioteca estándar de C++.
        Está implementada en el archivo de cabecera <vector>. emplace_back permite construir un nuevo elemento
        directamente en el lugar al final del vector, utilizando los argumentos proporcionados para llamar al constructor del elemento. (Explicación de la IA) */
        enemies.emplace_back(enemyTexture, sf::Vector2f(100.f * i, 200.f));
        innocents.emplace_back(innocentTexture, sf::Vector2f(100.f * i, 100.f));
    }
}

void Game::run()
{
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processEvents();
        if (!isMenuActive) {
            update(deltaTime);
        }
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (isMenuActive) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                isMenuActive = false; // Comienza el juego
                lives = 3; // Restablece las vidas
                score = 0; // Restablece la puntuación
                initializeGameObjects(); // Reinicia los objetos del juego
            }
        }
        else {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f clickPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    // Eliminar enemigos si se hace clic sobre ellos
                    for (auto it = enemies.begin(); it != enemies.end(); ) {
                        if (it->getBounds().contains(clickPosition)) {
                            it = enemies.erase(it); // Eliminar enemigo y actualizar iterador
                        }
                        else {
                            ++it; // Avanzar al siguiente enemigo
                        }
                    }

                    // Eliminar inocentes si se hace clic sobre ellos
                    for (auto it = innocents.begin(); it != innocents.end(); ) {
                        if (it->getBounds().contains(clickPosition)) {
                            it = innocents.erase(it); // Eliminar inocente y actualizar iterador
                            lives -= 1;
                        }
                        else {
                            ++it; // Avanzar al siguiente inocente
                        }
                    }
                }
            }
        }
    }
}

void Game::update(sf::Time deltaTime)
{
    crosshair.updatePosition(window);

    if (lives <= 0 && !isMenuActive) {
        sf::sleep(sf::seconds(2)); // delay antes de volver al menú, para contemplar la derrota jaja
        isMenuActive = true;
    }

    hud.update(lives, score);
}

void Game::render()
{
    window.clear();
    if (isMenuActive) {
        menu.draw(window);
    }
    else {
        for (const auto& enemy : enemies) {
            enemy.draw(window);
        }
        for (const auto& innocent : innocents) {
            innocent.draw(window);
        }
        crosshair.draw(window); // Dibujar el crosshair después de los objetos
        hud.draw(window);
    }
    window.display();
}