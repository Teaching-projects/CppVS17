#include "GameObject.hpp"
#include "TextureManager.hpp"
#include <iostream>

GameObject::GameObject(const char* textureName, int x, int y) : xpos(x), ypos(y) {
	objTexture = TextureManager::LoadTexture(textureName);
}

GameObject::~GameObject() {

}

void GameObject::Update() {
	
}

void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}


