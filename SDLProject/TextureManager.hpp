#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP
#include "Game.hpp"

class TextureManager {

public:

	static SDL_Texture* LoadTexture(const char* textureSheet);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
	static void DrawText( int x, int y, const char* text, SDL_Color color);
};

#endif /* TEXTUREMANAGER_HPP */