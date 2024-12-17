#include "Game.h"
#include <iostream>

Game::Game(float v0, float vFinal)
    : window(sf::VideoMode(800, 600), "Fast & Furious - Aceleración variable"),
    currentSpeedX(0.0f), currentSpeedY(0.0f), finalSpeed(vFinal),
    accelerationX(0.0f), accelerationY(0.0f) {

    // Crear el auto, es un BaseObject
    car = new BaseObject("../../Res/car.png");

    // Configurar escala del auto porque la textura es enorme
    sf::Vector2u textureSize = car->GetTextureSize();
    float desiredWidth = 150.0f;
    float scale = desiredWidth / textureSize.x;
    car->SetScale(scale);

    // Ubicar el auto en el centro de la pantalla
    car->SetPosition(sf::Vector2f(400.0f, 300.0f));
}

// Destructor
Game::~Game() {
    delete car; // porque se instancia con new...
}

void Game::Loop() {
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds(); // Delta time
        processEvents();
        update(dt);
        render();
    }
}

// Procesar eventos
void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

// Actualizar lógica del juego
void Game::update(float dt) {
    // Restablecer la aceleración
    accelerationX = 0.0f;
    accelerationY = 0.0f;

    // Aceleración basada en el teclado (teclas de flecha)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        accelerationX += 100.0f; // Acelerar a la derecha
        cout << "Acelerando" << endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        accelerationX -= 100.0f; // Acelerar a la izquierda
        cout << "Frenando" << endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        accelerationY -= 100.0f; // Acelerar hacia arriba
        cout << "Subiendo" << endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        accelerationY += 100.0f; // Acelerar hacia abajo
        cout << "Bajando" << endl;
    }

    //if ((currentSpeedX > 0 && accelerationX < 0) || (currentSpeedX < 0 && accelerationX > 0)) {
    //    currentSpeedX += (accelerationX < 0) ? -50 * dt : 50 * dt;
    //    if (std::abs(currentSpeedX) < 0.1f) {
    //        currentSpeedX = 0.0f;
    //    }
    //}
    //else {
    //    currentSpeedX += accelerationX * dt;
    //}

    //if ((currentSpeedY > 0 && accelerationY < 0) || (currentSpeedY < 0 && accelerationY > 0)) {
    //    currentSpeedY += (accelerationY < 0) ? -50 * dt : 50 * dt;
    //    if (std::abs(currentSpeedY) < 0.1f) {
    //        currentSpeedY = 0.0f;
    //    }
    //}
    //else {
    //    currentSpeedY += accelerationY * dt;
    //}

    currentSpeedX += accelerationX * dt;
    currentSpeedY += accelerationY * dt;

    // Limitar la velocidad máxima por normativas de emisiones de carbono (sino paga muchos impuestos)
    if (std::abs(currentSpeedX) > finalSpeed) currentSpeedX = finalSpeed * (currentSpeedX > 0 ? 1.0f : -1.0f);
    if (std::abs(currentSpeedY) > finalSpeed) currentSpeedY = finalSpeed * (currentSpeedY > 0 ? 1.0f : -1.0f);

    // Actualizar la posición del auto (x e y)
    sf::Vector2f pos = car->GetPosition();
    pos.x += currentSpeedX * dt;
    pos.y += currentSpeedY * dt;

    // Si el auto sale por el borde derecho, vuelve por el izquierdo
    if (pos.x > window.getSize().x) {
        pos.x = -150.0f;
    }

    // Si el auto sale por el borde izquierdo, vuelve por el derecho
    if (pos.x < -150.0f) {
        pos.x = window.getSize().x;
    }

    // Si el auto sale por el borde inferior, vuelve por el superior
    if (pos.y > window.getSize().y) {
        pos.y = -150.0f;
    }

    // Si el auto sale por el borde superior, vuelve por el inferior
    if (pos.y < -150.0f) {
        pos.y = window.getSize().y;
    }

    car->SetPosition(pos);
    car->Update(dt);
}

// Renderizar en la ventana
void Game::render() {
    window.clear(sf::Color::White); // Fondo blanco
    car->Draw(&window);
    window.display();
}
