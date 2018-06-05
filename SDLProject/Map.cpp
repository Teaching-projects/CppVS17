#include "Map.hpp"
#include "TextureManager.hpp"
#include <iostream>

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
				std::cout << "ship" << std::endl;
				TextureManager::Draw(water, srcR, destR);
				TextureManager::Draw(ship, srcR, destR);
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
