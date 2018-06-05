#include "Map.hpp"
#include "TextureManager.hpp"
#include <iostream>

Map::Map(int _baseOffsetX, int _baseOffsetY) : baseOffsetX(_baseOffsetX), baseOffsetY(_baseOffsetY) {
	water = TextureManager::LoadTexture("assets/water_flat.png");
	ship = TextureManager::LoadTexture("assets/ship.png");


	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			map[x][y] = 0;
		}
	}

	srcR.x = srcR.y = 0;
	destR.x = destR.y = 0;
	srcR.w = destR.w = 32;
	srcR.h = destR.h = 32;
}

Map::~Map() {

}

void Map::DrawMap() {
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
}
