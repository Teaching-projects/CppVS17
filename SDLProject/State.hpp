#ifndef STATE_HPP
#define STATE_HPP
#include "Game.hpp"

class State {
protected:
	SDL_Color Color = { 255, 255, 255 };
	Vector2D mousePos{-1,-1};
public:
	virtual void handleEvents(SDL_Event event) = 0;
	virtual void render() = 0;
};

#endif // STATE_HPP