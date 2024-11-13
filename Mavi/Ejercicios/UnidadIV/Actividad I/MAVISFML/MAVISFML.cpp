//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

//////Variables//////
Texture texture;
Sprite sprite1, sprite2, sprite3, sprite4;
int w, h;

///Punto de entrada a la aplicación///
int main() {
	//Dimensiones de la ventana, también sirven para calcular posiciones
	w = 800;
	h = 600;

	//Cargamos la textura del archivo
	texture.loadFromFile("..\\..\\res\\Unidad4_Assets\\crosshair.png");
	
	// Cargamos el material de cada sprite y le damos su posición inicial a cada uno
	// el "magic number" (mala práctica) "128" es porque rcircle.png es de 128x128px
	sprite1.setTexture(texture);
	sprite1.setPosition(w/2 - 128/2, h/2 - 128/2);

	//Creamos la ventana
	sf::RenderWindow App(sf::VideoMode(w, h, 32), "Crosshair");

	// Loop principal
	while (App.isOpen())
	{
		// Limpiamos la ventana
		App.clear();

		// Dibujamos la escena
		App.draw(sprite1);

		// Mostramos la ventana
		App.display();
	}

	return 0;
}
