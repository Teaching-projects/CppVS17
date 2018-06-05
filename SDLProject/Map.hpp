#ifndef MAP_HPP
#define MAP_HPP
#include "Game.hpp"

class Map {

public:
	Map(int _baseoffsetX, int _baseoffsetY);
	~Map();

	void DrawMap(int x, int y);
	bool SetField(int startX, int startY, int endX, int endY, int length);
	bool ValidCoord(int x, int y);
private:
	int baseOffsetX;
	int baseOffsetY;
	int size;
	SDL_Rect srcR, destR;

	SDL_Texture* water;
	SDL_Texture* ship;
	SDL_Texture* select;

	int map[10][10];

};


#endif /* MAP_HPP */