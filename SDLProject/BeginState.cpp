#include "BeginState.hpp"
#include "State.hpp"
#include "TextureManager.hpp"

BeginState::BeginState(Game* _game) : game(_game){}
BeginState::~BeginState() {}

void BeginState::handleEvents(SDL_Event event){
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		game->gameState = GameState::Prep;
	}
}

void BeginState::render() {
	TextureManager::DrawText(342, 20, "Torpedo", Color);
	TextureManager::DrawText(240, 70, "Kattints a folytatáshoz!", Color);
}
