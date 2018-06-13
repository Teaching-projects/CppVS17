#ifndef BEGINSTATE_HPP
#define BEGINSTATE_HPP
#include "Game.hpp"
#include "State.hpp"

class BeginState : public State {
	Game* game;
public:
	BeginState(Game* _game);
	~BeginState();
	void handleEvents(SDL_Event event);
	void render();
};

#endif // BEGINSTATE_HPP