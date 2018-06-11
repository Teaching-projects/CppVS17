#include "Game.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"

SDL_Renderer* Game::renderer = nullptr;
TTF_Font* Game::font = nullptr;
SDL_Color Color = { 255, 255, 255 };

Map* playerMap = nullptr;
Map* enemyMap = nullptr;

Vector2D mousePos;

bool win = false;
Ship ships[5];
int shipPrepCount = 0,
	shipStartEndCounter = 0;
int shipPlacement[4];
int prepErrorCode = 0,
	playerCounter = 0,
	playerShipCount = 17,
	enemyShipCount = 17;
std::string s;
const char* pchar;

Vector2D inputVectorStart{ -1, -1 };
Vector2D inputVectorEnd{ -1, -1 };


int placement[10][10] = {
{ 0,0,0,0,0,2,0,0,0,0 },
{ 0,0,0,0,0,2,0,0,0,0 },
{ 0,0,0,0,0,2,0,0,0,0 },
{ 0,2,2,2,2,2,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0 },
{ 2,2,2,2,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,2,2,2,0,0,2,0 },
{ 0,0,0,0,0,0,0,0,2,0 },
{ 0,0,0,0,0,0,0,0,0,0 },
};

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
		playerMap = new Map(0, 0);
		enemyMap = new Map(448, 0);
		enemyMap->Load(placement);
		ships[0] = Ship{ "Anyahajó", inputVectorStart, inputVectorStart, 5 , false };
		ships[1] = Ship{ "Csatahajó", inputVectorStart, inputVectorStart, 4 , false };
		ships[2] = Ship{ "Cirkáló", inputVectorStart, inputVectorStart, 3 , false };
		ships[3] = Ship{ "Tengeralattjáró", inputVectorStart, inputVectorStart, 3 , false };
		ships[4] = Ship{ "Romboló", inputVectorStart, inputVectorStart, 2 , false };
		
	}else {
		isRunning = false;
	}
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	SDL_GetMouseState(&mousePos.x, &mousePos.y);

	switch (gameState) {
		case GameState::Begin:
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				gameState = GameState::Prep;
			}
			break;
		case GameState::Prep:
			
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				//ha start {-1,-1}
				if (inputVectorStart.x == -1 && inputVectorStart.y == -1) {
					// olvassuk be az eger pozt
					inputVectorStart.x = mousePos.x;
					inputVectorStart.y = mousePos.y;
					// convert to coord
					playerMap->ScreenToMapCoord(inputVectorStart, inputVectorStart);

					if (playerMap->ValidCoord(inputVectorStart)) {
						playerMap->SetSelector(inputVectorStart);
						shipStartEndCounter++;
					}
				}
				//ha start már nem {-1, -1}, ha end {-1, -1}
				else if (inputVectorEnd.x == -1 && inputVectorEnd.y == -1) {
					// olvassuk be az eger pozt
					inputVectorEnd.x = mousePos.x;
					inputVectorEnd.y = mousePos.y;
					// convert to coord
					playerMap->ScreenToMapCoord(inputVectorEnd, inputVectorEnd);

					// validak egymashoz kepest ?
					playerMap->ClearSelector(inputVectorStart);
					prepErrorCode = playerMap->ValidOrientation(inputVectorStart, inputVectorEnd);
					if(prepErrorCode == 0)
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
					gameState = GameState::Play;
				}
			}
			break;
		case GameState::Play:
			if (playerCounter % 2 == 0) {
				if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
					
					inputVectorStart.x = mousePos.x;
					inputVectorStart.y = mousePos.y;
					// convert to coord
					enemyMap->ScreenToMapCoord(inputVectorStart, inputVectorStart);
					if (!enemyMap->HasBeenChecked(inputVectorStart)) {
						enemyShipCount += enemyMap->UpdateTile(inputVectorStart);	
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
				playerShipCount += playerMap->UpdateTile(guess);
				playerCounter++;
			}

			if (enemyShipCount == 0) {
				win = true;
				gameState = GameState::End;
			}
			if (playerShipCount == 0) {
				win = false;
				gameState = GameState::End;
			}
			
			break;
		case GameState::End:
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				isRunning = false;
			}
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
	
	switch (gameState) {
	case GameState::Begin:
		TextureManager::DrawText(342, 20, "Torpedo", Color);
		TextureManager::DrawText(240, 70, "Kattints a folytatáshoz!", Color);
		break;
	case GameState::Prep:
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
		
		break;
	case GameState::Play:
		s = std::string("17/") + std::to_string(playerShipCount);
		pchar = s.c_str();
		TextureManager::DrawText(340, 10, "Játékos", Color);
		TextureManager::DrawText(350, 40, pchar, Color);
		
		s = std::string("17/") + std::to_string(enemyShipCount);
		pchar = s.c_str();
		TextureManager::DrawText(360, 250, "Gép", Color);
		TextureManager::DrawText(350, 280, pchar, Color);

		playerMap->DrawMap(mousePos.x, mousePos.y);
		enemyMap->DrawMap(mousePos.x, mousePos.y);

		break;
	case GameState::End:
		if (win) {
			TextureManager::DrawText(318, 20, "Gratulálok!", Color);
		}else{
			TextureManager::DrawText(270, 20, "Majd legközelebb...", Color);
		}

		s = std::string("17/") + std::to_string(playerShipCount);
		pchar = s.c_str();
		TextureManager::DrawText(150, 100, "Játékos", Color);
		TextureManager::DrawText(160, 130, pchar, Color);
		s = std::string("17/") + std::to_string(enemyShipCount);
		pchar = s.c_str();
		TextureManager::DrawText(550, 100, "Gép", Color);
		TextureManager::DrawText(540, 130, pchar, Color);

		TextureManager::DrawText(260, 250, "Kattints a kilépéshez!", Color);
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


