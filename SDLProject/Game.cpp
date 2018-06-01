#include "Game.hpp"
#include "GameObject.hpp"
#include "Map.hpp"

SDL_Renderer* Game::renderer = nullptr;
Map* map = nullptr;

Game::Game() {

}

Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (window) {
			std::cout << "ablak kesz..." << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer kesz..." << std::endl;
		}

		isRunning = true;
		gameState = GameState::Begin;
		std::cout << gameState << std::endl;
	}else {
		isRunning = false;
	}
	map = new Map();
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			gameState = GameState::Play;
		}
		
	}

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update() {
}

void Game::render() {
	SDL_RenderClear(renderer);
	
	switch (gameState) {
	case GameState::Begin: 
		break;
	case GameState::Play:
		map->DrawMap();
		break;
	case GameState::End:
		break;
	default:
		break;
	}
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

bool Game::running() {
	return isRunning;
}


