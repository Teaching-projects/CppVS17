#ifndef MAP_HPP
#define MAP_HPP
#include "Game.hpp"

class Map {

public:
	Map();
	~Map();

	void LoadMap(int arr[20][25]);
	void DrawMap();

private:
	SDL_Rect srcR, destR;

	SDL_Texture* water;
	SDL_Texture* ship;

	int map[20][25];

};


#endif /* MAP_HPP */