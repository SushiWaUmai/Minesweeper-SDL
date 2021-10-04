#include "SDL.h"
#include "log.h"

SDL_Texture* LoadTexture(const char* filePath, SDL_Renderer* _renderer) {
	SDL_Surface* image = SDL_LoadBMP(filePath);
	LOG_ASSERT(image, "Failed to load image");

	SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, image);
	LOG_ASSERT(texture, "Failed to create texture");

	SDL_FreeSurface(image);

	LOG_TRACE("Load {0} into memory", filePath);

	return texture;
}

bool InRect(int x, int y, SDL_Rect& r) {
	return (x >= r.x) && (y >= r.y) &&
		(x < r.x + r.w) && (y < r.y + r.h);
}