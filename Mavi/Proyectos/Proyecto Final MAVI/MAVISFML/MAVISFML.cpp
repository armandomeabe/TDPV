//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Includes.h"
#include "GameManager.h"

int main() {
	RenderWindow App(VideoMode(800, 600, 32), "Final");
	auto gm = new GameManager(&App); // la envío al heap, 'gm' queda en el stack pero solo el ptr.
	gm->Start();
	return 0;
}
