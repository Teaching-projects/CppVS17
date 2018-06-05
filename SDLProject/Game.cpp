#include "Game.hpp"
#include "GameObject.hpp"
#include "Map.hpp"

SDL_Renderer* Game::renderer = nullptr;
TTF_Font* Game::font = nullptr;
SDL_Color Color = { 35, 255, 0 };

Map* playerMap = nullptr;
Map* enemyMap = nullptr;
int mouseX, mouseY;


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
		font = TTF_OpenFont("Ubuntu.ttf", 36);

		isRunning = true;
		gameState = GameState::Begin;
		
	}else {
		isRunning = false;
	}
	playerMap = new Map(0,0);
	enemyMap = new Map(448, 0);
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
		TextureManager::DrawText(342, 20, "Torpedo", Color);
		break;
	case GameState::Play:
		SDL_GetMouseState(&mouseX, &mouseY);
		playerMap->DrawMap(mouseX, mouseY);
		enemyMap->DrawMap(mouseX, mouseY);
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


