//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;

// Plataformas
// Utilizando el mismo gráfico, escálelo y reproduzca (de manera aproximada) la siguiente
// imagen. Este sería un caso típico de un juego de plataformas.

//////Variables//////
Texture texturePlatform;
std::vector<Sprite> platforms; // También podía ser un arreglo

///Punto de entrada a la aplicación///
int main() {
    // Cargamos la textura del archivo de plataforma
    if (!texturePlatform.loadFromFile("D:\\Developer\\FICH\\TDPV\\Mavi\\Ejercicios\\res\\plataforma.jpg")) {
        std::cerr << "Error: No se pudo cargar el archivo plataforma.jpg" << std::endl; // En caso que loadFromFile devuelva false
        return -1;
    }

    // Creamos la ventana
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Escenario de Plataformas");

    // Datos del gráfico de barras (alturas en píxeles)
    // El horizontal lo manejo aparte
    std::vector<float> heights = { 100, 150, 200, 250, 300 };
    float barWidth = 50.0f; // Ancho de cada barra
    float gap = 20.0f; // Espacio entre barras, por eso "gap"

    // Configuramos los sprites de las barras
    for (size_t i = 0; i < heights.size(); ++i) {
        Sprite platform;
        platform.setTexture(texturePlatform);

        // Escalar la barra para que tenga el ancho y la altura deseados
        float scaleX = barWidth / texturePlatform.getSize().x;
        float scaleY = heights[i] / texturePlatform.getSize().y;
        platform.setScale(scaleX, scaleY);

        // Posicionar la barra en el gráfico
        // Ajustar la posición Y para que las barras crezcan hacia arriba
        platform.setPosition(i * (barWidth + gap), 600 - heights[i]);

        // Hay que agregarlo al vector de plataformas
        platforms.push_back(platform);
    }

    // Agregar una barra horizontal
    // En realidad podría usar el mismo sprite adentro del for
    Sprite horizontalPlatform;
    horizontalPlatform.setTexture(texturePlatform);

    // Escalar la barra horizontal
    float horizontalScaleX = 600.0f / texturePlatform.getSize().x; // Ancho de la barra horizontal
    float horizontalScaleY = 20.0f / texturePlatform.getSize().y;  // Altura fija para la barra horizontal
    horizontalPlatform.setScale(horizontalScaleX, horizontalScaleY);

    // Posicionar la barra horizontal
    horizontalPlatform.setPosition(400.0f, 300.0f); // Ajustar la posición de la barra horizontal, a ojo :-)

    platforms.push_back(horizontalPlatform);

    // Loop principal
    while (App.isOpen())
    {
        // Procesamos los eventos
        sf::Event event;
        while (App.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                App.close();
        }

        // Limpiamos la ventana
        App.clear();

        // Dibujamos las plataformas
        for (const auto& platform : platforms) {
            App.draw(platform);
        }

        // Mostramos la ventana
        App.display();
    }

    return 0;
}