//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace sf;

//////Clase enemy, modela los enemigos que aparecen aleatoriamente//////
class Enemy {
public:
    Sprite sprite; // El sprite del enemigo
    static const Vector2f size; // Tamaño del enemigo

    // Constructor, recibe una dirección de una Texture (ya tiene que existir) esto me permite usar la misma textura para muchos enemigos
    Enemy(const Texture& texture) {
        sprite.setTexture(texture); // Le ponemos la textura al enemigo
        // Escalar al enemigo para que tenga el tamaño 
        sprite.setScale(
            size.x / texture.getSize().x,
            size.y / texture.getSize().y
        );
        setRandomPosition(); // Poner al enemigo en una posición random
    }

    // Dibuja al enemigo en la ventana
    void draw(RenderWindow& window) {
        window.draw(sprite);
    }

    // Cambia al enemigo de lugar al azar
    void setRandomPosition() {
        // Calcula una posición random dentro de la ventana
        // static_cast es para convertir el resultado a float
        float x = static_cast<float>(std::rand() % (800 - static_cast<int>(size.x)));
        float y = static_cast<float>(std::rand() % (600 - static_cast<int>(size.y)));
        this->sprite.setPosition(x, y); // Lo coloca en la posición random. this-> queda raro en C++... en C# "this." es una práctica habitual. Es opcional porque this es por defecto.
    }

    // Devuelve los límites del enemigo (para saber si le disparamos)
    FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }
};

// Definimos el tamaño del enemigo
const Vector2f Enemy::size(128, 128); // Después de experimentar encontré que menos de 128 se hace molesto de apuntarle rápido

//////Clase Crosshair//////
class Crosshair {
public:
    Sprite sprite; // El dibujo de la mira
    static const Vector2f size; // Cuán grande queremos que sea la mira

    // Constructor para la mira
    Crosshair(const Texture& texture) {
        sprite.setTexture(texture); // Le ponemos la textura a la mira
        // Escalamos la mira para que tenga el tamaño que queremos
        sprite.setScale(
            size.x / texture.getSize().x,
            size.y / texture.getSize().y
        );
        // Colocamos el origen en el centro para que apunte bien, por eso los "/ 2" para que sea a la mitad
        sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    }

    // Actualiza la posición de la mira según el mouse
    void updatePosition(const RenderWindow& window) {
        // mapPixelToCoords es genial porque así no tengo que estar poniendole la posición .x y .y
        // uso directamente setPosition al sprite sacando la posicion del mouse y listo, por eso la dependencia SFML/Window.hpp
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        sprite.setPosition(mousePos);
    }

    // Dibuja la mira en la ventana
    // También gracias a SFML/Window.hpp, "window" parece ser una referencia directa a la ventana con todas sus propiedades y métodos como draw(...)
    void draw(RenderWindow& window) {
        window.draw(sprite);
    }
};

// Definimos el tamaño de la mira aquí
const Vector2f Crosshair::size(32, 32); // Chiquita porque la ventana es de 800x600.

///Punto de entrada a la aplicación///
int main() {
    // Inicializar el generador de números aleatorios
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Cargamos las texturas
    Texture enemyTexture, crosshairTexture, victoryTexture;
    if (!enemyTexture.loadFromFile("../../res/Unidad4_Assets/et.png") ||
        !crosshairTexture.loadFromFile("../../res/Unidad4_Assets/crosshair.png") ||
        !victoryTexture.loadFromFile("../../res/Unidad4_Assets/victoria.png")) {
        return -1; // Salimos si no se pudieron cargar las texturas, loadfromfile devuelve algo diferente a 1 que se puede interpretar como false en ese caso
    }

    // Crear la ventana
    RenderWindow App(VideoMode(800, 600), "FIGHT!!!!");
    App.setMouseCursorVisible(false); // Ocultar el cursor del mouse

    // Crear la mira (crosshair)
    Crosshair crosshair(crosshairTexture);

    // Vector para almacenar los enemigos
    std::vector<Enemy> enemies;

    // Contador de enemigos derrotados
    int defeatedEnemies = 0;

    // Sprite para la imagen de victoria (añadido extra-consigna, le agrega gratificación al final)
    Sprite victorySprite(victoryTexture);

    // Loop principal
    while (App.isOpen()) {
        Event event;
        while (App.pollEvent(event)) {
            if (event.type == Event::Closed) {
                App.close(); // Cierra la ventana si la cerramos
            }

            // Detectar clic del mouse
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                // Obtenemos donde hicimos clic en la ventana
                Vector2f mousePos = App.mapPixelToCoords(Mouse::getPosition(App));

                // Verificar si le pegamos a un enemigo
                for (auto it = enemies.begin(); it != enemies.end();) {
                    if (it->getBounds().contains(mousePos)) { //cada enemigo tiene "getBounds" y a cada bound se le puede preguntar si contiene una posición, esto resuelve todo
                        it = enemies.erase(it); // Borramos al enemigo si le dimos
                        defeatedEnemies++;
                        break; // Salimos del loop porque ya le pegamos a uno, en teoría sin esto podrías matar 2 aliens de un solo tiro
                    }
                    else {
                        ++it; // Seguimos buscando si no le dimos a este (al que apunta el iterador it)
                    }
                }
            }
        }

        // Actualizar posición de la mira
        crosshair.updatePosition(App);

        // Agregar un enemigo si no hay ninguno y no hemos ganado aún
        if (enemies.empty() && defeatedEnemies < 5) {
            enemies.emplace_back(enemyTexture);
        }

        // Limpiar la ventana
        App.clear(Color::Black);

        if (defeatedEnemies >= 5) {
            // Dibujar imagen de victoria
            App.draw(victorySprite);
        }
        else {
            // Dibujar enemigos, se recorre todo el vector por cada frame. auto& es como var de C#, pero para direcciones de memoria y no para instancias directamente.
            // Similar a recorrer con un iterator.
            for (auto& enemy : enemies) {
                enemy.draw(App);
            }

            // Dibujar la mira
            crosshair.draw(App);
        }

        // Mostrar la ventana
        App.display();
    }

    return 0;
}