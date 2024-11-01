// Querido compañero de clases <3 este código no tiene copyright ni limitaciones de licencia, como todo lo que subo a este repo
// no obstante recordá que el espíritu de abrir el código es compartir para que todos aprendamos y no duplicar la tarea para entregarla sin comprenderla
// siempre que necesites una mano podés contactarme. ¡Nos vemos cursando!

//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream> // Biblioteca para cout

using namespace sf;

//////Variables//////
Event evt;

///Punto de entrada a la aplicación///
int main()
{
    /////Creamos la ventana//////
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Que Ventana horrible");
    /////Loop principal//////
    while (App.isOpen())
    {
        while (App.pollEvent(evt)) {

            /////Procesar eventos//////
            switch (evt.type)
            {
                /////Eventos de ventana//////
            case sf::Event::Closed:
                std::cout << "Evento: Closed" << std::endl;
                App.close();
                break;
            case sf::Event::Resized:
                std::cout << "Evento: Resized - New Width: " << evt.size.width << " New Height: " << evt.size.height << std::endl;
                break;
            case sf::Event::LostFocus:
                std::cout << "Evento: LostFocus" << std::endl;
                break;
            case sf::Event::GainedFocus:
                std::cout << "Evento: GainedFocus" << std::endl;
                break;

                /////Eventos de teclado//////
            case sf::Event::TextEntered:
                std::cout << "Evento: TextEntered - Character: " << static_cast<char>(evt.text.unicode) << std::endl;
                break;
            case sf::Event::KeyPressed:
                std::cout << "Evento: KeyPressed - Key: " << evt.key.code << std::endl;
                break;
            case sf::Event::KeyReleased:
                std::cout << "Evento: KeyReleased - Key: " << evt.key.code << std::endl;
                break;

                /////Eventos de mouse//////
            case sf::Event::MouseWheelMoved:
                std::cout << "Evento: MouseWheelMoved - Delta: " << evt.mouseWheel.delta << std::endl;
                break;
            case sf::Event::MouseButtonPressed:
                std::cout << "Evento: MouseButtonPressed - Button: " << evt.mouseButton.button
                    << " x: " << evt.mouseButton.x << " y: " << evt.mouseButton.y << std::endl;
                break;
            case sf::Event::MouseButtonReleased:
                std::cout << "Evento: MouseButtonReleased - Button: " << evt.mouseButton.button
                    << " x: " << evt.mouseButton.x << " y: " << evt.mouseButton.y << std::endl;
                break;
            case sf::Event::MouseMoved:
                std::cout << "Evento: MouseMoved - x: " << evt.mouseMove.x << " y: " << evt.mouseMove.y << std::endl;
                break;
            case sf::Event::MouseEntered:
                std::cout << "Evento: MouseEntered" << std::endl;
                break;
            case sf::Event::MouseLeft:
                std::cout << "Evento: MouseLeft" << std::endl;
                break;

                /////Eventos de joystick//////
            case sf::Event::JoystickButtonPressed:
                std::cout << "Evento: JoyButtonPressed - JoystickId: " << evt.joystickButton.joystickId
                    << " Button: " << evt.joystickButton.button << std::endl;
                break;
            case sf::Event::JoystickButtonReleased:
                std::cout << "Evento: JoyButtonReleased - JoystickId: " << evt.joystickButton.joystickId
                    << " Button: " << evt.joystickButton.button << std::endl;
                break;
            case sf::Event::JoystickMoved:
                std::cout << "Evento: JoyMoved - JoystickId: " << evt.joystickMove.joystickId
                    << " Axis: " << evt.joystickMove.axis << " Position: " << evt.joystickMove.position << std::endl;
                break;

            default:
                std::cout << "Evento: Otro tipo de evento" << std::endl;
                break;
            }
        }
    }
    return 0;
}