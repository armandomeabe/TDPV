//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

//////Variables//////
Texture texture;
Sprite sprite1, sprite2, sprite3, sprite4;

///Punto de entrada a la aplicación///
int main() {
	// SNIPER (ACTIVIDAD 1)
	//Cargamos la textura del archivo
	texture.loadFromFile("D:\\Developer\\FICH\\TDPV\\Mavi\\Ejercicios\\res\\rcircle.png");
	
	// Cargamos el material de cada sprite y le damos su posición inicial a cada uno
	// el "magic number" (mala práctica) "128" es porque rcircle.png es de 128x128px
	sprite1.setTexture(texture);
	sprite1.setPosition(0, 0);

	sprite2.setTexture(texture);
	sprite2.setPosition((800 - 128), 0);

	sprite3.setTexture(texture);
	sprite3.setPosition(0, (600 - 128));
	
	sprite4.setTexture(texture);
	sprite4.setPosition((800 - 128), (600 - 128));

	//Creamos la ventana
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Sniper");

	bool direction = false;

	// Loop principal
	while (App.isOpen())
	{
		// Limpiamos la ventana
		App.clear();

		// Dibujamos la escena
		App.draw(sprite1);
		App.draw(sprite2);
		App.draw(sprite3);
		App.draw(sprite4);

		// Mostramos la ventana
		App.display();
	}

	return 0;
}
