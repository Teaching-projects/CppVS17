#include "Map.hpp"
#include "TextureManager.hpp"
#include <iostream>
#include <stdlib.h>

Map::Map(int _baseOffsetX, int _baseOffsetY) : baseOffsetX(_baseOffsetX), baseOffsetY(_baseOffsetY) {
	water = TextureManager::LoadTexture("assets/water_flat.png");
	ship = TextureManager::LoadTexture("assets/ship.png");
	select = TextureManager::LoadTexture("assets/cursor.png");

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

bool Map::SetField(int startX, int startY, int endX, int endY, int length) {
	startX = startX / 32;
	startY = startY / 32;
	endX = endX / 32;
	endY = endY / 32;
	if (ValidCoord(startX, startY) && ValidCoord(endX,endY)) {
		if (startX == endX || startY == endY) {
			if ((abs(startX - endX) + abs(startY - endY) + 1) >= length) {
				if (startX == endX) {
					for (int i = startY; i <= endY; i++) {
						map[startX][i] = 1;
					}
				}
				else {
					for (int i = startX; i <= endX; i++) {
						map[i][startY] = 1;
					}
				}
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool Map::ValidCoord(int x, int y) {
	if (x <= 9 && x >= 0 && y <= 9 && y >= 0) {
		return true;
	}
	return false;
}

void Map::DrawMap(int mX, int mY) {
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {

			destR.x = (x * 32) + baseOffsetX;
			destR.y = (y * 32) + baseOffsetY;

			switch (map[x][y]) {
			case 0:
				TextureManager::Draw(water, srcR, destR);
				break;
			case 1:
				TextureManager::Draw(water, srcR, destR);
				TextureManager::Draw(ship, srcR, destR);
				break;
			case 2: // Talalt
				TextureManager::Draw(water, srcR, destR);
				
				break;
			case 3: // Nem talalt
				TextureManager::Draw(water, srcR, destR);
				
				break;
			default:
				break;
			}
		}
	}

	if (mX > (baseOffsetX) && mX < (baseOffsetX + 320) && mY > (baseOffsetY) && mY < (baseOffsetY + 320)) {
		destR.x = ((mX / 32) * 32);
		destR.y = ((mY / 32) * 32);
		std::cout<< mX << " , " << mY << " -> " << destR.x << " , " << destR.y << std::endl;
		TextureManager::Draw(select, srcR, destR);
	}
}
