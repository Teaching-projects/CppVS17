#include "Game.hpp"
#include "GameObject.hpp"
#include "Map.hpp"

SDL_Renderer* Game::renderer = nullptr;
TTF_Font* Game::font = nullptr;
SDL_Color Color = { 144, 164, 174 };

Map* playerMap = nullptr;
Map* enemyMap = nullptr;
int mouseX, mouseY;

bool win = false;
bool ships[5];
int shipPrepCount = 0;
int shipPlacement[4];


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
				gameState = GameState::Prep;
			}
			break;
		case GameState::Prep:
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				SDL_GetMouseState(&mouseX, &mouseY);
				

				ships[shipPrepCount] = true;
				shipPrepCount++;

				if (shipPrepCount == 6) {
					gameState = GameState::Play;
				}
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
		TextureManager::DrawText(240, 70, "Kattints a folytatáshoz!", Color);
		break;
	case GameState::Prep:
		TextureManager::DrawText(420, 20, "Helyezd el hajóidat!", Color);
		if (!ships[0]) {
			TextureManager::DrawText(480, 70, "Hajó(1)!", Color);
		}
		else if (!ships[1]) {
			TextureManager::DrawText(480, 70, "Hajó(2)!", Color);
		}
		else if (!ships[2]) {
			TextureManager::DrawText(480, 70, "Hajó(3)!", Color);
		}
		else if (!ships[3]) {
			TextureManager::DrawText(480, 70, "Hajó(4)!", Color);
		}
		else if (!ships[4]) {
			TextureManager::DrawText(480, 70, "Hajó(5)!", Color);
		}else{
			TextureManager::DrawText(400, 70, "Kattints a folytatáshoz!", Color);
		}
		
		
		SDL_GetMouseState(&mouseX, &mouseY);
		playerMap->DrawMap(mouseX, mouseY);
		
		break;
	case GameState::Play:
		SDL_GetMouseState(&mouseX, &mouseY);
		playerMap->DrawMap(mouseX, mouseY);
		enemyMap->DrawMap(mouseX, mouseY);
		break;
	case GameState::End:
		if (win) {
			TextureManager::DrawText(318, 20, "Gratulálok!", Color);
		}else{
			TextureManager::DrawText(270, 20, "Majd legközelebb...", Color);
		}
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


