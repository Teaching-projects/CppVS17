#ifndef ENDSTATE_HPP
#define ENDSTATE_HPP
#include "Game.hpp"
#include "State.hpp"

class EndState : public State {
	Game* game;
public:
	EndState(Game* _game);
	~EndState();
	void handleEvents(SDL_Event event);
	void render();
};

#endif // ENDSTATE_HPP