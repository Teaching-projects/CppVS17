#include <SDL.h>
#undef main
#include "Game.hpp"

Game* game = nullptr;

int main(int argc, char *args[]) {

	const int fps = 60;
	const int frameDelay = 1000 / fps;
	unsigned int frameStart = 0;
	int frameTime = 0;

	game = new Game();
	game->init("Torpedo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 768, 320, false);

	while (game->running()) {

		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
		
	}

	game->clean();

	return 0;
}

