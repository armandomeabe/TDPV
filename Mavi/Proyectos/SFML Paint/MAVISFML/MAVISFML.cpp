//////Bibliotecas//////
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

int main()
{
    // Creamos la ventana
    RenderWindow window(VideoMode(800, 600), "Mini Paint, salvando las distancias...");

    // Variables para el color y tamaño del pincel
    Color brushColor = Color::Black;
    float brushSize = 5.0f; // experimentar con esto!

    // Vector para almacenar los círculos dibujados
    // si... los vuelvo a dibujar por cada iteración!
    // nunca dije que era eficiente...
    std::vector<CircleShape> circles;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) // para que se pueda cerrar la ventana
                window.close();

            // Cambiar el color del pincel usando los números (no tengo teclado numérico pero con los de arriba de las letras al menos funciona)
            if (event.type == Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case Keyboard::Num1:
                    brushColor = Color::Black;
                    break;
                case Keyboard::Num2:
                    brushColor = Color::Red;
                    break;
                case Keyboard::Num3:
                    brushColor = Color::Green;
                    break;
                case Keyboard::Num4:
                    brushColor = Color::Blue;
                    break;
                case Keyboard::Num5:
                    brushColor = Color::Yellow;
                    break;
                }

                // Cambiar el tamaño del pincel con las flechas arriba y abajo
                // este código viene de "yapa" y me ayudó copilot porque no tenía idea
                if (event.key.code == Keyboard::Up)
                    brushSize = std::min(brushSize + 1.0f, 50.0f); // "min" es parte del namespace std y dados dos argumentos elije el mínimo
                else if (event.key.code == Keyboard::Down)
                    brushSize = std::max(brushSize - 1.0f, 1.0f); // idem pero con máximo
            }
        }

        // Dibujar cuando se mantiene presionado el botón izquierdo del mouse
        // si miramos la teoría de la unidad IV, estamos usando la forma unbuffered
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            CircleShape circle(brushSize);
            circle.setFillColor(brushColor);
            circle.setPosition(Mouse::getPosition(window).x - brushSize, Mouse::getPosition(window).y - brushSize);
            circles.push_back(circle);
        }

        // Limpiar la ventana (se vuelve a pintar todo de blanco)
        window.clear(Color::White);

        // Dibujar todos los círculos de vuelta
        // "auto" en C++ es como "var" en C#, sigue siendo fuertemente tipado porque el tipo se determina en tiempo de compilación y no se puede cambiar en runtime
        for (const auto& circle : circles)
            window.draw(circle);

        // Mostrar la ventana
        window.display();
    }

    return 0;
}