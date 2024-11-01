//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream> // Biblioteca para cout

using namespace sf;

/////Variables//////
sf::Sprite cursor;
sf::Texture mat_cursor;
/////Punto de entrada a la aplicación//////
int main()
{
    ///// Creamos el sprite para el cursor//////
    sf::Event evt;
    if (!mat_cursor.loadFromFile("..\\..\\..\\Recursos\\Unidad4_Assets\\crosshair.png")) {
        std::cerr << "Error al cargar el archivo de textura." << std::endl;
        return -1; // Salir si la carga falla
    }
    cursor.setTexture(mat_cursor);
    cursor.setPosition(0, 0);
    /////Creamos la ventana//////
    sf::RenderWindow App(sf::VideoMode(1920, 1080, 32), "Que Ventana horrible");
    /////Ocultamos el cursor del sistema/////
    App.setMouseCursorVisible(false);
    /////Loop principal//////
    while (App.isOpen())
    {
        while (App.pollEvent(evt)) {
            /////Procesar eventos//////
            switch (evt.type) {
                /////Si se cerro la ventana//////
            case sf::Event::Closed:
                App.close();
                break;
            case sf::Event::MouseMoved:
                /////Actualizamos la posición del sprite con/////
                /////la informacion del evento del mouse/////
                cursor.setPosition(evt.mouseMove.x, evt.mouseMove.y);
                break;
            }
        }
        App.clear(sf::Color::White);
        App.draw(cursor);
        App.display();
    }
    return 0;
}