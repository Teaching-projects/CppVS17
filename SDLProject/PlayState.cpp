#include "PlayState.hpp"
#include "State.hpp"
#include "TextureManager.hpp"

PlayState::PlayState(Game* _game, Map* _playerMap, Map* _enemyMap) : game(_game), playerMap(_playerMap), enemyMap(_enemyMap), playerCounter(0) {
	enemyMap->Load();
}
PlayState::~PlayState() {}

void PlayState::handleEvents(SDL_Event event) {
	SDL_GetMouseState(&mousePos.x, &mousePos.y);
	if (playerCounter % 2 == 0) {
		if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {

			inputVector.x = mousePos.x;
			inputVector.y = mousePos.y;
			// convert to coord
			enemyMap->ScreenToMapCoord(inputVector, inputVector);
			if (!enemyMap->HasBeenChecked(inputVector)) {
				game->enemyShipCount += enemyMap->UpdateTile(inputVector);
				playerCounter++;
			}
		}
	}
	else {
		Vector2D guess;
		do {
			guess.x = rand() % 10;
			guess.y = rand() % 10;
		} while (playerMap->HasBeenChecked(guess));
		game->playerShipCount += playerMap->UpdateTile(guess);
		playerCounter++;
	}

	if (game->enemyShipCount == 0) {
		game->win = true;
		game->gameState = GameState::End;
	}
	if (game->playerShipCount == 0) {
		game->win = false;
		game->gameState = GameState::End;
	}
}

void PlayState::render() {
	std::string s;
	const char* pchar;
	s = std::string("17/") + std::to_string(game->playerShipCount);
	pchar = s.c_str();
	TextureManager::DrawText(340, 10, "Játékos", Color);
	TextureManager::DrawText(350, 40, pchar, Color);

	s = std::string("17/") + std::to_string(game->enemyShipCount);
	pchar = s.c_str();
	TextureManager::DrawText(360, 250, "Gép", Color);
	TextureManager::DrawText(350, 280, pchar, Color);

	playerMap->DrawMap(mousePos.x, mousePos.y);
	enemyMap->DrawMap(mousePos.x, mousePos.y);
}
