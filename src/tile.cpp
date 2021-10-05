#include "tile.h"
#include "log.h"
#include "utils.h"
#include "game.h"
#include <sstream>

SDL_Texture* Tile::tileTextures[8];
SDL_Texture* Tile::hiddenTexture;
SDL_Texture* Tile::bombTexture;

void Tile::Init(SDL_Renderer* _renderer)
{
	for (uint32_t i = 0; i < 8; i++) {
		std::stringstream ss;
		ss << "res/tile" << i + 1 << ".bmp";

		tileTextures[i] = LoadTexture(ss.str().c_str(), _renderer);
	}

	hiddenTexture = LoadTexture("res/hidden.bmp", _renderer);
	bombTexture = LoadTexture("res/bomb.bmp", _renderer);
}

Tile::Tile(int x, int y) {
	dst.x = x * CELL_WIDTH;
	dst.y = y * CELL_HEIGHT;
	dst.w = CELL_WIDTH;
	dst.h = CELL_HEIGHT;
}

void Tile::Render(SDL_Renderer* _renderer) {
	if (isExposed) {
		if (surroundedBombs != -1) {
			SDL_RenderCopy(_renderer, tileTextures[surroundedBombs], NULL, &dst);
		}
		else {
			SDL_RenderCopy(_renderer, bombTexture, NULL, &dst);
		}
	}
	else {
		SDL_RenderCopy(_renderer, hiddenTexture, NULL, &dst);
	}
}

void Tile::Handle(SDL_MouseButtonEvent _mouseEvent) {
	if (_mouseEvent.button == SDL_BUTTON_LEFT) {
		if (InRect(_mouseEvent.x, _mouseEvent.y, dst)) {
			LOG_INFO("Tile Clicked: ({0}, {1})", dst.x / CELL_WIDTH, dst.y / CELL_HEIGHT);
			Expose();
		}
	}
}
