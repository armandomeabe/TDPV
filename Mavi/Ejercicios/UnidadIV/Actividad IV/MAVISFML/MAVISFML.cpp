//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

//////Variables//////
Texture squareTexture, circleTexture;
Sprite shape; // Sprite que mostrará la figura actual, que puede cambiar
const float speed = 200.0f; // Rapidez (no velocidad porque la velocidad es un vector) de movimiento del sprite
const Vector2f size(128, 128); // Tamaño deseado para ambos sprites

///Punto de entrada a la aplicación///
int main() {
    // Cargamos las texturas de los archivos usando rutas correctas y relativas
    if (!squareTexture.loadFromFile("../../res/Unidad4_Assets/cuad_yellow.png")) {
        return -1; // Salir si no se pudo cargar la textura del cuadrado
    }
    if (!circleTexture.loadFromFile("../../res/Unidad4_Assets/rcircleg.png")) {
        return -1; // Salir si no se pudo cargar la textura del círculo
    }

    // Configuramos el sprite inicial como cuadrado
    shape.setTexture(squareTexture);
    shape.setScale(
        size.x / squareTexture.getSize().x,
        size.y / squareTexture.getSize().y
    ); // Redimensionamos el sprite para que sea de 128x128 píxeles
    shape.setPosition(400 - size.x / 2, 300 - size.y / 2); // Centrado en la ventana

    // Creamos la ventana
    RenderWindow App(VideoMode(800, 600, 32), "Atrapado");

    // Reloj para manejar el tiempo entre frames (ver comentario más abajo).
    Clock clock;

    // Loop principal
    while (App.isOpen()) {
        Event event;
        while (App.pollEvent(event)) {
            if (event.type == Event::Closed)
                App.close();

            if (event.type == Event::KeyPressed) {
                // Cambiar la textura al presionar la barra espaciadora
                if (event.key.code == Keyboard::Space) {
                    if (shape.getTexture() == &squareTexture) {
                        shape.setTexture(circleTexture);
                    }
                    else {
                        shape.setTexture(squareTexture);
                    }
                    // Asegurarse de que el tamaño se mantenga constante
                    shape.setScale(
                        size.x / shape.getTexture()->getSize().x,
                        size.y / shape.getTexture()->getSize().y
                    );
                }
            }
        }

        // Calcular el tiempo transcurrido desde el último frame...
        // Esto lo encontré porque en la unidad III tenía el problema de que el sprite rotativo no rotaba a una velocidad constante
        // y esto resultó ser porque no necesariamente va a pasar siempre el mismo tiempo entre frame y frame
        float deltaTime = clock.restart().asSeconds();

        // Movimiento del sprite con las teclas de dirección
        // Bug conocido: Si combino dos teclas del teclado, se escapa de los límites de la ventana. TO-DO.
        // No deja de ser un bug menor comparado con que si uso un Vector2f puedo combinar direcciones y moverlo en diagonal!
        Vector2f movement(0.0f, 0.0f);
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            movement.x -= speed * deltaTime;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            movement.x += speed * deltaTime;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            movement.y -= speed * deltaTime;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            movement.y += speed * deltaTime;
        }

        // Actualizar la posición del sprite
        shape.move(movement);

        // Obtener los límites del sprite y de la ventana 
        FloatRect bounds = shape.getGlobalBounds();
        Vector2u windowSize = App.getSize();

        // Asegurarme de que el sprite no salga de los límites de la ventana (TO-DO: Bug)
        if (bounds.left < 0) {
            shape.setPosition(0, bounds.top);
        }
        if (bounds.top < 0) {
            shape.setPosition(bounds.left, 0);
        }
        if (bounds.left + bounds.width > windowSize.x) {
            shape.setPosition(windowSize.x - bounds.width, bounds.top);
        }
        if (bounds.top + bounds.height > windowSize.y) {
            shape.setPosition(bounds.left, windowSize.y - bounds.height);
        }

        App.clear();
        App.draw(shape);
        App.display();
    }

    return 0;
}