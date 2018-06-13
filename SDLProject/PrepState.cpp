#include "PrepState.hpp"
#include "State.hpp"
#include "TextureManager.hpp"

PrepState::PrepState(Game* _game, Map* _playerMap) : game(_game), playerMap(_playerMap), inputVectorStart({ -1,-1 }), inputVectorEnd({ -1,-1 }), prepErrorCode(0), shipStartEndCounter(0), shipPrepCount(0) {}

PrepState::~PrepState() {}

void PrepState::handleEvents(SDL_Event event) {
	SDL_GetMouseState(&mousePos.x, &mousePos.y);
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		if (inputVectorStart.x == -1 && inputVectorStart.y == -1) {
			inputVectorStart.x = mousePos.x;
			inputVectorStart.y = mousePos.y;
			playerMap->ScreenToMapCoord(inputVectorStart, inputVectorStart);

			if (playerMap->ValidCoord(inputVectorStart)) {
				playerMap->SetSelector(inputVectorStart);
				shipStartEndCounter++;
			}
		}
		else if (inputVectorEnd.x == -1 && inputVectorEnd.y == -1) {
			inputVectorEnd.x = mousePos.x;
			inputVectorEnd.y = mousePos.y;
			playerMap->ScreenToMapCoord(inputVectorEnd, inputVectorEnd);

			playerMap->ClearSelector(inputVectorStart);
			prepErrorCode = playerMap->ValidOrientation(inputVectorStart, inputVectorEnd);
			if (prepErrorCode == 0)
				prepErrorCode = playerMap->ValidLength(ships[shipPrepCount].length, inputVectorStart, inputVectorEnd);
			if (prepErrorCode == 0)
				prepErrorCode = playerMap->ValidPlacement(inputVectorStart, inputVectorEnd);


			if (prepErrorCode == 0) {
				shipStartEndCounter++;
				shipPrepCount++;
				inputVectorStart.x = inputVectorStart.y = inputVectorEnd.x = inputVectorEnd.y = -1;
			}
			else {
				shipStartEndCounter = 0;
				inputVectorStart.x = inputVectorStart.y = inputVectorEnd.x = inputVectorEnd.y = -1;
			}
		}
		if (shipPrepCount == 5 && prepErrorCode == 0) {
			game->gameState = GameState::Play;
		}
	}
}

void PrepState::render() {
	std::string s;
	const char* pchar;
	TextureManager::DrawText(420, 20, "Helyezd el hajóidat!", Color);
	if (!ships[shipPrepCount].placed && shipPrepCount <= 4) {
		TextureManager::DrawText(480, 70, ships[shipPrepCount].name, Color);
		s = std::to_string(ships[shipPrepCount].length) + std::string(" mezõ");
		pchar = s.c_str();
		TextureManager::DrawText(495, 100, pchar, Color);
		if (shipStartEndCounter % 2 == 0) {
			TextureManager::DrawText(400, 130, "Add meg a kezdõpozíciót!", Color);
		}
		else {
			TextureManager::DrawText(400, 130, "Add meg a végpozíciót!", Color);
		}

		if (prepErrorCode == 1) {
			TextureManager::DrawText(400, 170, "Az elhelyezés hibás!", Color);
		}
		else if (prepErrorCode == 2) {
			TextureManager::DrawText(400, 170, "A terület nem szabad", Color);
		}
		else if (prepErrorCode == 4) {
			TextureManager::DrawText(400, 170, "A méret kicsi!", Color);
		}
		else if (prepErrorCode == 5) {
			TextureManager::DrawText(400, 170, "A méret nagy!", Color);
		}
	}
	if (shipPrepCount > 4) {
		TextureManager::DrawText(400, 70, "Kattints a folytatáshoz!", Color);
	}

	playerMap->DrawMap(mousePos.x, mousePos.y);
}
