#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char* textureSheet) {

	SDL_Surface* tmpSrf = IMG_Load(textureSheet);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSrf);
	SDL_FreeSurface(tmpSrf);

	return tex;
};

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}

void TextureManager::DrawText(int x, int y, const char* text, SDL_Color color) {
	int length = strlen(text);
	int width = length * 12;
	SDL_Surface* surfaceText = TTF_RenderText_Solid(Game::font, text, color);
	SDL_Texture* textureText = SDL_CreateTextureFromSurface(Game::renderer, surfaceText);
	SDL_FreeSurface(surfaceText);

	SDL_Rect Message_rect;

	Message_rect.x = x;
	Message_rect.y = y;
	Message_rect.w = width;
	Message_rect.h = 28;

	SDL_RenderCopy(Game::renderer, textureText, NULL, &Message_rect);
}