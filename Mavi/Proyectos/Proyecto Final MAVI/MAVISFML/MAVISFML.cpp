//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
///Punto de entrada a la aplicación 2 ///
#include "Includes.h"

int main() {
	////Creamos la ventana
	//sf::RenderWindow App(sf::VideoMode(800, 600, 32),
	//	"Que ventana horrible");
	//// Loop principal
	//while (App.isOpen())
	//{
	//	// Limpiamos la ventana
	//	App.clear();
	//	//Dibujamos la escena
	//	 // Mostramos la ventana
	//	App.display();
	//}
	//return 0;

	RenderWindow App(VideoMode(1200, 1000, 32), "EL SHERIFF");
	auto gm = new GameManager(&App); // la envío al heap, 'gm' queda en el stack pero solo el ptr.
	gm->Start();
	return 0;
}
