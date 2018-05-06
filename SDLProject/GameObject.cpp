#include "GameObject.hpp"
#include "TextureManager.hpp"
#include <iostream>

GameObject::GameObject(const char* textureName, int x, int y) : xpos(x), ypos(y) {
	objTexture = TextureManager::LoadTexture(textureName);
}

GameObject::~GameObject() {

}

void GameObject::Update() {

	xpos++;
	ypos++;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.h = 32;
	destRect.w = 32;
	destRect.x = xpos;
	destRect.y = ypos;

}

void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}


