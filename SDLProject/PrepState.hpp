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
		Ship{ "Anyahajó", inputVectorStart, inputVectorStart, 5 , false },
		Ship{ "Csatahajó", inputVectorStart, inputVectorStart, 4 , false },	
		Ship{ "Cirkáló", inputVectorStart, inputVectorStart, 3 , false },
		Ship{ "Tengeralattjáró", inputVectorStart, inputVectorStart, 3 , false },
		Ship{ "Romboló", inputVectorStart, inputVectorStart, 2 , false }
	};

public:
	PrepState(Game* _game, Map* _playerMap);
	~PrepState();
	void handleEvents(SDL_Event event);
	void render();
};

#endif // PREPSTATE_HPP