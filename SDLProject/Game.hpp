#ifndef GAME_HPP
#define GAME_HPP
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>

struct Vector2D {
	int x;
	int y;
};

struct Ship {
	const char* name;
	Vector2D start;
	Vector2D end;
	int length;
	bool placed;
};

struct Data {
	int shots;
	int hits;
};


enum GameState {
	Begin, Prep, Play, End
};

class Game {
public:

	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running();

	static SDL_Renderer* renderer;
	static TTF_Font* font;

private:
	GameState gameState;
	int cnt;
	bool isRunning;
	SDL_Window* window;
};


#endif /* GAME_HPP */ 