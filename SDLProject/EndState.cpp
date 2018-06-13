#include "EndState.hpp"
#include "State.hpp"
#include "TextureManager.hpp"

EndState::EndState(Game* _game) : game(_game) {}
EndState::~EndState() {}

void EndState::handleEvents(SDL_Event event) {
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		game->isRunning = false;
	}
}

void EndState::render() {
	std::string s;
	const char* pchar;
	if (game->win) {
		TextureManager::DrawText(318, 20, "Gratulálok!", Color);
	}
	else {
		TextureManager::DrawText(270, 20, "Majd legközelebb...", Color);
	}

	s = std::string("17/") + std::to_string(game->playerShipCount);
	pchar = s.c_str();
	TextureManager::DrawText(150, 100, "Játékos", Color);
	TextureManager::DrawText(160, 130, pchar, Color);
	s = std::string("17/") + std::to_string(game->enemyShipCount);
	pchar = s.c_str();
	TextureManager::DrawText(550, 100, "Gép", Color);
	TextureManager::DrawText(540, 130, pchar, Color);

	TextureManager::DrawText(260, 250, "Kattints a kilépéshez!", Color);
}
