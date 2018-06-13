#include "Map.hpp"
#include "TextureManager.hpp"
#include <iostream>
#include <math.h>

Map::Map(int _baseOffsetX, int _baseOffsetY) : baseOffsetX(_baseOffsetX), baseOffsetY(_baseOffsetY) {
	water = TextureManager::LoadTexture("assets/water_flat.png");
	ship = TextureManager::LoadTexture("assets/ship.png");
	select = TextureManager::LoadTexture("assets/cursor.png");
	miss = TextureManager::LoadTexture("assets/miss.png");
	hit = TextureManager::LoadTexture("assets/hit.png");


	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			map[x][y] = 0;
		}
	}

	srcR.w = destR.w = 32;
	srcR.h = destR.h = 32;
}

Map::~Map() {

}

void Map::Load() {
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			map[x][y] = placement[x][y];
		}
	}
}

bool Map::HasBeenChecked(Vector2D pos) {
	return !(map[pos.x][pos.y] == 0 || map[pos.x][pos.y] == 2 || map[pos.x][pos.y] == 1);
}

int Map::UpdateTile(Vector2D pos) {
	if (map[pos.x][pos.y] == 0) {
		map[pos.x][pos.y] = 4;
		return 0;
	}
	else if (map[pos.x][pos.y] == 2) {
		map[pos.x][pos.y] = 3;
		return -1;
	}
	else if (map[pos.x][pos.y] == 1) {
		map[pos.x][pos.y] = 3;
		return -1;
	}
	return 0;
}

void Map::ScreenToMapCoord(Vector2D screenPos, Vector2D& mapPos) {
	mapPos.x = (screenPos.x - baseOffsetX) / 32;
	mapPos.y = (screenPos.y - baseOffsetY) / 32;
	ValidCoord(mapPos);
}

bool Map::ValidCoord(Vector2D& pos) {
	if (pos.x <= 9 && pos.x >= 0 && pos.y <= 9 && pos.y >= 0) {
		return true;
	}
	pos.x = -1;
	pos.y = -1;
	return false;
}

int Map::ValidLength(int length, Vector2D start, Vector2D end) {
	int shipLength = sqrt(pow((start.x - end.x), 2) + pow((start.y - end.y), 2)) + 1;
	if (shipLength < length) {
		return 4;
	}

	if (shipLength > length) {
		return 5;
	}

	return 0;
}

int Map::ValidPlacement(Vector2D start, Vector2D end) {
	int anchor = 0;
	int iterStart = 0;
	int iterEnd = 0;
	int xDif = start.x - end.x;
	int yDif = start.y - end.y;

	if (xDif == 0) {
		anchor = start.x;
		if (start.y < end.y) {
			iterStart = start.y;
			iterEnd = end.y;
		}
		else {
			iterStart = end.y;
			iterEnd = start.y;
		}
		for (int i = iterStart; i <= iterEnd; i++) {
			
			if (map[anchor][i] != 0) {
				return 2;
			}
		}
		for (int i = iterStart; i <= iterEnd; i++) {
			map[anchor][i] = 1;
		}
	}
	else {
		anchor = start.y;
		if (start.x < end.x) {
			iterStart = start.x;
			iterEnd = end.x;
		}
		else {
			iterStart = end.x;
			iterEnd = start.x;
		}

		for (int i = iterStart; i <= iterEnd; i++) {
			if (map[i][anchor] != 0) {
				return 2;
			}
		}
		for (int i = iterStart; i <= iterEnd; i++) {
			map[i][anchor] = 1;
		}
	}

	return 0;
}


void Map::PlaceShips(Vector2D start, Vector2D end) {

}

int Map::ValidOrientation(Vector2D& start, Vector2D& end) {
	if (start.x != end.x && start.y != end.y) {
		start.x = start.y = end.x = end.y = -1;
		return 1;
	}
	return 0;
}

void Map::DrawMap(int mX, int mY) {
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {

			destR.x = (x * 32) + baseOffsetX;
			destR.y = (y * 32) + baseOffsetY;

			TextureManager::Draw(water, srcR, destR);
			switch (map[x][y]) {
			case 0:
				break;
			case 1: // Jatekos
				TextureManager::Draw(ship, srcR, destR);
				break;
			case 2: // Gep
				//TextureManager::Draw(select, srcR, destR);
				break;
			case 3: // Talalt
				TextureManager::Draw(hit, srcR, destR);
				break;
			case 4: // Nem talalt
				TextureManager::Draw(miss, srcR, destR);
				break;
			case 5: // Nem talalt
				TextureManager::Draw(select, srcR, destR);
				break;
			default:
				break;
			}
		}
	}

	if (mX > (baseOffsetX) && mX < (baseOffsetX + 320) && mY > (baseOffsetY) && mY < (baseOffsetY + 320)) {
		destR.x = ((mX / 32) * 32);
		destR.y = ((mY / 32) * 32);
		
		TextureManager::Draw(select, srcR, destR);
	}
}

void Map::SetSelector(Vector2D pos) {
	map[pos.x][pos.y] = 5;
}

void Map::ClearSelector(Vector2D pos) {
	map[pos.x][pos.y] = 0;
}
