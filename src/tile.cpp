#include "tile.h"
#include "log.h"
#include "utils.h"
#include <sstream>

SDL_Texture* Tile::tileTextures[8];
SDL_Texture* Tile::hiddenTexture;

void Tile::Init(SDL_Renderer* _renderer)
{
	for (uint32_t i = 0; i < 8; i++) {
		std::stringstream ss;
		ss << "res/tile" << i + 1 << ".bmp";

		tileTextures[i] = LoadTexture(ss.str().c_str(), _renderer);
	}
}

void Tile::Expose() {
}

void Tile::Flag() {
}

void Tile::Render(SDL_Renderer* _renderer) {
	if (isExposed) {
		SDL_RenderCopy(_renderer, tileTextures[surroundedBombs], NULL, &dst);
	}
	else {
	}
}