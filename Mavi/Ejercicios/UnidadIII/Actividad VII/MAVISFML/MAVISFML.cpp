//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

//////Variables//////
Texture texture, texture_blue;
Sprite sprite1, sprite2, sprite3, sprite4, sprite_blue;

///Punto de entrada a la aplicación///
int main() {

	//Cargamos las texturas desde archivos (bcircle.png es la nueva)
	texture.loadFromFile("D:\\Developer\\FICH\\TDPV\\Mavi\\Ejercicios\\res\\rcircle.png");
	texture_blue.loadFromFile("D:\\Developer\\FICH\\TDPV\\Mavi\\Ejercicios\\res\\bcircle.png");
	
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

	sprite_blue.setTexture(texture_blue);
	// El punto azul tiene 268px de lado, eso significa que si hiciera "800/2 = 400" y esa fuera mi posición horizontal, me quedaría desfasado hacia la derecha
	// porque no estaría contemplando el ancho del punto mismo por lo que necesito que ese ancho (268) también sea afectado por el cociente para quedar correctamente en el centro
	// Lo mismo con el alto
	sprite_blue.setPosition((800 - 268) / 2, (600-268) / 2); 

	//Creamos la ventana
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Sniper nuevo");

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
		App.draw(sprite_blue);

		// Mostramos la ventana
		App.display();
	}

	return 0;
}
