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