#include <SDL.h>
#undef main
#include "Game.hpp"

Game* game = nullptr;

int main(int argc, char *args[]) {
	game = new Game();
	game->init("Main ablak", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, false);

	while (game->running()) {
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}

