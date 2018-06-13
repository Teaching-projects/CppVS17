#ifndef GAME_HPP
#define GAME_HPP
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <stdlib.h>
#include <string>

struct Vector2D {
	int x;
	int y;
};

enum GameState {
	Begin, Prep, Play, End
};

class Game {
public:

	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleGameEvents();
	void render();
	void clean();
	bool running();

	GameState gameState;
	
	static SDL_Renderer* renderer;
	static TTF_Font* font;

	bool win;
	int playerShipCount = 17,
		enemyShipCount = 17;

	bool isRunning;
private:
	SDL_Window* window;
};


#endif /* GAME_HPP */ 