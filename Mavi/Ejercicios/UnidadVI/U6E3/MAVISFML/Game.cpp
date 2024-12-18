#include "Game.h"
#include "iostream"

Game::Game(int width, int height)
    : window(VideoMode(width, height), "Bounce"),
    ball("../../Res/ball.png"),
    gravity(10.0f),
    bounceFactor(0.7f) // Rebote al 70% de la velocidad
{
    ball.SetPosition(Vector2f(300, 0));
    ball.SetScale(0.2f); // La imagen de la bola es gigante asi que la dejamos al 20%
}

void Game::Run() {
    Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        ProcessEvents();
        Update(dt);
        Render();
    }
}

void Game::ProcessEvents() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
    }
}

void Game::Update(float dt) {
    Vector2f velocity = ball.GetVelocity();
    Vector2f position = ball.GetPosition();

    // Aplicar gravedad
    ball.AddAcceleration(Vector2f(0, gravity));

    auto  realBallSize = (ball.GetTextureSize().y * ball.GetScale().y);

    // Verificar colisión con el suelo
    if (position.y + realBallSize >= window.getSize().y) {

        std::cout << velocity.y * bounceFactor << std::endl;
        if (velocity.y * bounceFactor < 10) {
            return; // La idea de este if era que si el movimiento ya es imperceptible, que deje de gastar CPU en achicar el rebote a valores infimos... no funciono, sigue ocupando el mismo % de CPU.
        }

        // Rebote: al usar -velocity le invierto el sentido en Y, bounceFactor es un multiplicador para agrandar el rebote nada mas
        velocity.y = -velocity.y * bounceFactor;
        // Sin el bouncefactor queda rebotando como en una serie infinita donde cada salto es mas pequeno que el anterior

        // Asegurarme de que el auto no quede debajo del suelo, le reseteo la posicion en el tope inferior
        position.y = window.getSize().y - realBallSize;
    }

    ball.SetVelocity(velocity);
    ball.SetPosition(position);
    ball.Update(dt);
}

void Game::Render() {
    window.clear();
    window.clear(sf::Color::White); // Con el fondo blanco no se notan las imperfecciones en el recorte de la bola
    ball.Draw(&window);
    window.display();
}
