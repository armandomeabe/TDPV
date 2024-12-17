#include "Game.h"

int main() {
    float velocidadInicial = 200.0f; // Velocidad inicial V0
    float velocidadFinal = 9800.0f;   // Velocidad final Vfinal

    Game game(velocidadInicial, velocidadFinal);
    game.Loop();

    return 0;
}
