#include "Game.hpp"
#include "GameObject.hpp"
#include "Map.hpp"

SDL_Renderer* Game::renderer = nullptr;
Map* playerMap = nullptr;
Map* enemyMap = nullptr;

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
			SDL_SetRenderDrawColor(renderer, 52, 52, 52, 255);
			std::cout << "renderer kesz..." << std::endl;
		}

		isRunning = true;
		gameState = GameState::Begin;
		std::cout << gameState << std::endl;
	}else {
		isRunning = false;
	}
	playerMap = new Map(0,160);
	enemyMap = new Map(420, 160);
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);


	switch (gameState) {
		case GameState::Begin:
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				gameState = GameState::Play;
			}
			break;
		case GameState::Play:
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				gameState = GameState::End;
			}
			break;
		case GameState::End:
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				gameState = GameState::Begin;
			}
			break;
		default:

			break;
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
		playerMap->DrawMap();
		enemyMap->DrawMap();
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


