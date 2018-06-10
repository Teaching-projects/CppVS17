#ifndef MAP_HPP
#define MAP_HPP
#include "Game.hpp"

class Map {

public:
	Map(int _baseoffsetX, int _baseoffsetY);
	~Map();

	void DrawMap(int x, int y);
	bool ValidCoord(Vector2D& pos);
	int ValidLength(int length, Vector2D start, Vector2D end);
	int ValidOrientation(Vector2D& start, Vector2D& end);
	int ValidPlacement(Vector2D start, Vector2D end);
	void PlaceShips(Vector2D start, Vector2D end);
	void ScreenToMapCoord(Vector2D screenPos, Vector2D& mapPos);
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