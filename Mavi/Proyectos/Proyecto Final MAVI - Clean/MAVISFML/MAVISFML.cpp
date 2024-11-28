//////Bibliotecas//////
#include "Includes.h"
#include "GameManager.h"

int main() {
	RenderWindow App(VideoMode(1200, 800, 32), "Armand Gunman!");
	auto gm = new GameManager(&App); // la envío al heap, 'gm' queda en el stack pero solo el ptr.
	gm->Start();
	return 0;
}
