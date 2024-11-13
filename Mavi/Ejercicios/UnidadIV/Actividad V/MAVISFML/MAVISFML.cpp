//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

///Punto de entrada a la aplicación///
int main() {
    // Crear la ventana con un tamaño inicial
    RenderWindow App(VideoMode(800, 600), "Adaptacion", Style::Resize | Style::Close);

    // Limitar el framerate, si no uso esto, el CPU se va al 100% permanente aunque no "haga nada" (re-dibujando la ventana negra nomás)
    App.setFramerateLimit(60);

    // Loop principal
    while (App.isOpen()) {
        Event event;
        while (App.pollEvent(event)) {
            if (event.type == Event::Closed) {
                App.close();
            }

            // Manejar del cambio de tamaño de la ventana, es un evento más como los del mouse o del teclado, o del joystick
            if (event.type == Event::Resized) {
                // Obtener el nuevo tamaño de la ventana
                Vector2u newSize(event.size.width, event.size.height);

                // Ver que el tamaño no sea menor a 100x100 ni mayor a 1000x1000
                if (newSize.x < 100) newSize.x = 100;
                if (newSize.y < 100) newSize.y = 100;
                if (newSize.x > 1000) newSize.x = 1000;
                if (newSize.y > 1000) newSize.y = 1000;

                // Ajustar el tamaño de la ventana al tamaño permitido
                App.setSize(newSize);
            }
        }

        App.clear(Color::Black);
        App.display();
    }

    return 0;
}