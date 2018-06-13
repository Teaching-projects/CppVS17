#ifndef PREPSTATE_HPP
#define PREPSTATE_HPP
#include "Game.hpp"
#include "Map.hpp"
#include "State.hpp"

struct Ship {
	const char* name;
	Vector2D start;
	Vector2D end;
	int length;
	bool placed;
};

class PrepState : public State {
	Game* game;
	Vector2D inputVectorStart;
	Vector2D inputVectorEnd;
	Map* playerMap;
	int prepErrorCode;
	int shipStartEndCounter;
	int shipPrepCount;

	Ship ships[5] = {
		Ship{ "Anyahaj�", inputVectorStart, inputVectorStart, 5 , false },
		Ship{ "Csatahaj�", inputVectorStart, inputVectorStart, 4 , false },	
		Ship{ "Cirk�l�", inputVectorStart, inputVectorStart, 3 , false },
		Ship{ "Tengeralattj�r�", inputVectorStart, inputVectorStart, 3 , false },
		Ship{ "Rombol�", inputVectorStart, inputVectorStart, 2 , false }
	};

public:
	PrepState(Game* _game, Map* _playerMap);
	~PrepState();
	void handleEvents(SDL_Event event);
	void render();
};

#endif // PREPSTATE_HPP