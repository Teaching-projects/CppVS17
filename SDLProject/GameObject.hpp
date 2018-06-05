#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include "Game.hpp"
#include "TextureManager.hpp"

class GameObject {
	
public:
	GameObject(const char* textureSheet, int x, int y);
	~GameObject();

	void Update();
	void Render();
	int xpos, ypos;
private:
	

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
};

#endif /* GAMEOBJECT_HPP */
