//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

//////Variables//////
Texture redCircleTexture, blueCircleTexture;
std::vector<Sprite> circles; // Vector para almacenar todos los círculos, recordar que se van a re-dibujar todos asi que hay que recorrer todos por cada frame

///Punto de entrada a la aplicación///
int main() {
    // Cargamos las texturas de los archivos usando rutas relativas
    if (!redCircleTexture.loadFromFile("../../res/Unidad4_Assets/rcircle.png")) {
        return -1; // Salir si no se pudo cargar la textura del círculo rojo
    }
    if (!blueCircleTexture.loadFromFile("../../res/Unidad4_Assets/rcircleb.png")) {
        return -1; // Salir si no se pudo cargar la textura del círculo azul
    }

    // Creamos la ventana
    RenderWindow App(VideoMode(800, 600, 32), "Splats");

    // Loop principal
    while (App.isOpen()) {
        Event event;
        while (App.pollEvent(event)) {
            if (event.type == Event::Closed)
                App.close();

            if (event.type == Event::MouseButtonPressed) {
                Vector2f mousePos = App.mapPixelToCoords(Mouse::getPosition(App));

                if (event.mouseButton.button == Mouse::Left) {
                    // Crear y posicionar un nuevo círculo rojo
                    Sprite redCircle;
                    redCircle.setTexture(redCircleTexture);
                    redCircle.setPosition(mousePos.x - redCircleTexture.getSize().x / 2,
                        mousePos.y - redCircleTexture.getSize().y / 2);
                    circles.push_back(redCircle); // Agregar al vector de círculos
                }
                else if (event.mouseButton.button == Mouse::Right) {
                    // Crear y ubicar un nuevo círculo azul
                    Sprite blueCircle;
                    blueCircle.setTexture(blueCircleTexture);
                    blueCircle.setPosition(mousePos.x - blueCircleTexture.getSize().x / 2,
                        mousePos.y - blueCircleTexture.getSize().y / 2);
                    circles.push_back(blueCircle); // agregar al vector de círculos
                }
            }
        }

        // Limpiar la ventana
        App.clear();

        // Dibujar todos los círculos almacenados en el vector
        // entiendo que los círculos no cambian de posición en esta aplicación, pero si no hago esto
        // tengo que hacer una lógica en la que pregunto si un círculo dado ya fue dibujado o si debo dibujarlo por primera vez...
        for (const auto& circle : circles) {
            App.draw(circle);
        }

        // Mostrar la ventana
        App.display();
    }

    return 0;
}