#include "Game.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"
#include "BeginState.hpp"
#include "PrepState.hpp"
#include "PlayState.hpp"
#include "EndState.hpp"

SDL_Renderer* Game::renderer = nullptr;
TTF_Font* Game::font = nullptr;

BeginState* beginState = nullptr;
PrepState* prepState = nullptr;
PlayState* playState = nullptr;
EndState* endState = nullptr;

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

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
		}

		TTF_Init();
		font = TTF_OpenFont("Ubuntu.ttf", 24);

		isRunning = true;
		win = false;
		gameState = GameState::Begin;
		playerMap = new Map(0, 0);
		enemyMap = new Map(448, 0);

		beginState = new BeginState(this);
		prepState = new PrepState(this, playerMap);
		playState = new PlayState(this, playerMap, enemyMap);
		endState = new EndState(this);
		
		
	}else {
		isRunning = false;
	}
}

void Game::handleGameEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (gameState) {
		
		case GameState::Begin:
			beginState->handleEvents(event);
			break;
		case GameState::Prep:
			prepState->handleEvents(event);
			break;
		case GameState::Play:
			playState->handleEvents(event);
			break;
		case GameState::End:
			endState->handleEvents(event);
			break;
		default:

			break;
	}

	if(event.type == SDL_QUIT)
	{
		isRunning = false;
	}
}

void Game::render() {
	SDL_RenderClear(renderer);
	std::string s;
	const char* pchar;

	switch (gameState) {
	case GameState::Begin:
		beginState->render();
		break;
	case GameState::Prep:
		prepState->render();
		break;
	case GameState::Play:
		playState->render();
		break;
	case GameState::End:
		endState->render();
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


