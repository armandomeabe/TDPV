#include "Game.h"
#include <iostream>

// Constructor
Game::Game(float v0, float vFinal)
    : window(sf::VideoMode(800, 600), "Fast & Furious"), currentSpeed(v0), finalSpeed(vFinal) {

    // Crear el auto usando BaseObject
    car = new BaseObject("../../Res/car.png");

    // Configurar escala del auto (la textura es gigante)
    sf::Vector2u textureSize = car->GetTextureSize();
    float desiredWidth = 150.0f;
    float scale = desiredWidth / textureSize.x;
    car->SetScale(scale);

    // Posicionar el auto inicialmente a la izquierda,
    car->SetPosition(sf::Vector2f(0.0f, 300.0f));
}

// Destructor
Game::~Game() {
    delete car;
}

// Bucle principal
void Game::Loop() {
    while (window.isOpen() && currentSpeed <= finalSpeed) {
        float dt = clock.restart().asSeconds(); // Delta time
        processEvents();
        update(dt);
        render();
    }

    std::cout << "Velocidad final alcanzada: " << currentSpeed << std::endl;
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update(float dt) {
    // Obtener posición actual del auto
    sf::Vector2f pos = car->GetPosition();
    pos.x += currentSpeed * dt; // Mover el auto horizontalmente velocidad actual por DT (para consistencia independientemente de los FPS)

    // Si el auto sale del borde derecho, respawn en el lado izquierdo
    if (pos.x > window.getSize().x) {
        pos.x = -150.0f; // reaparece fuera del borde izquierdo
        currentSpeed += 50.0f; // fasterrr
        std::cout << "Nueva velocidad: " << currentSpeed << std::endl;
    }

    // Actualizar la posición y el objeto/auto
    car->SetPosition(pos);
    //car->AddAcceleration(Vector2f(10, 0));
    car->Update(dt);
}

void Game::render() {
    window.clear(sf::Color::Black);
    car->Draw(&window);
    window.display();
}
