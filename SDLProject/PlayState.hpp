#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP
#include "Game.hpp"
#include "Map.hpp"
#include "State.hpp"

class PlayState : public State {
	Game* game;
	Map* playerMap;
	Map* enemyMap;
	int playerCounter = 0;
	Vector2D inputVector;

public:
	PlayState(Game* _game, Map* _playerMap, Map* _enemyMap);
	~PlayState();
	void handleEvents(SDL_Event event);
	void render();
};

#endif // PLAYSTATE_HPP