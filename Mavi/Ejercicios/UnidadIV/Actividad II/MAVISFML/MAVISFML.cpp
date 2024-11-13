//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

//////Variables//////
Texture texture;
Sprite sprite1, sprite2, sprite3, sprite4;

// Variables adicionales para manejar el arrastre
bool isDragging = false;  // Indica si estamos arrastrando un sprite
Sprite* draggingSprite = nullptr;  // Puntero al sprite que se está arrastrando, esto de crear instancias* que apuntan a nullptr lo vimos en POO en Ing. en Inf de la FICH, espero que sea válido.
Vector2f offset;  // Desplazamiento entre el mouse y el sprite al empezar a arrastrar

///Punto de entrada a la aplicación///
int main() {
    // Cargamos la textura del archivo usando una ruta relativa
    if (!texture.loadFromFile("../../res/Unidad4_Assets/rcircle.png")) {
        return -1;  // Salir si no se pudo cargar la textura
    }

    // Configuramos cada sprite con la textura y su posición inicial
    // Se vienen un montón de "magic numbers", los 800 son el ancho, los 600 son el alto y los 128 son el lado del sprite
    sprite1.setTexture(texture);
    sprite1.setPosition(0, 0);

    sprite2.setTexture(texture);
    sprite2.setPosition((800 - 128), 0);

    sprite3.setTexture(texture);
    sprite3.setPosition(0, (600 - 128));

    sprite4.setTexture(texture);
    sprite4.setPosition((800 - 128), (600 - 128));

    // Creamos la ventana
    RenderWindow App(VideoMode(800, 600, 32), "Sniper draggeable");

    while (App.isOpen()) {
        Event event;
        while (App.pollEvent(event)) {
            if (event.type == Event::Closed)
                App.close();

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2f mousePos = App.mapPixelToCoords(Mouse::getPosition(App));

                    // Ver si el mouse está sobre algún sprite
                    // getGlobalBounds (vs getLocalBounds): "In simple terms: global bounds = local bounds + transformations and since you most of the time want to deal with the transformed position, scale or rotation, the global bounds become more useful than the local ones"
                    // ver: https://stackoverflow.com/questions/70502500/whats-the-difference-between-getlocalbounds-and-getglobalbounds-in-sfml-c
                    if (sprite1.getGlobalBounds().contains(mousePos)) {
                        isDragging = true;
                        draggingSprite = &sprite1;
                        offset = mousePos - sprite1.getPosition();
                    }
                    else if (sprite2.getGlobalBounds().contains(mousePos)) {
                        isDragging = true;
                        draggingSprite = &sprite2;
                        offset = mousePos - sprite2.getPosition();
                    }
                    else if (sprite3.getGlobalBounds().contains(mousePos)) {
                        isDragging = true;
                        draggingSprite = &sprite3;
                        offset = mousePos - sprite3.getPosition();
                    }
                    else if (sprite4.getGlobalBounds().contains(mousePos)) {
                        isDragging = true;
                        draggingSprite = &sprite4;
                        offset = mousePos - sprite4.getPosition();
                    }
                }
            }

            if (event.type == Event::MouseButtonReleased) {
                if (event.mouseButton.button == Mouse::Left) {
                    isDragging = false;
                    draggingSprite = nullptr;
                }
            }

            if (event.type == Event::MouseMoved) {
                if (isDragging && draggingSprite) {
                    Vector2f mousePos = App.mapPixelToCoords(Mouse::getPosition(App));
                    draggingSprite->setPosition(mousePos - offset);
                }
            }
        }

        // Limpiar la ventana
        App.clear();

        // Dibujamos cada sprite
        App.draw(sprite1);
        App.draw(sprite2);
        App.draw(sprite3);
        App.draw(sprite4);

        // Mostrar la ventana
        App.display();
    }

    return 0;
}