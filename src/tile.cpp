#include "tile.h"
#include "log.h"
#include "utils.h"
#include "game.h"
#include <sstream>

SDL_Texture* Tile::tileTextures[9];
SDL_Texture* Tile::hiddenTexture;
SDL_Texture* Tile::bombTexture;
SDL_Texture* Tile::flagTexture;

void Tile::Init(SDL_Renderer* _renderer)
{
	for (uint32_t i = 0; i < 9; i++) {
		std::stringstream ss;
		ss << "res/tile" << i << ".bmp";

		tileTextures[i] = LoadTexture(ss.str().c_str(), _renderer);
	}

	hiddenTexture = LoadTexture("res/hidden.bmp", _renderer);
	bombTexture = LoadTexture("res/bomb.bmp", _renderer);
	flagTexture = LoadTexture("res/flag.bmp", _renderer);
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
		if (isFlagged) {
			SDL_RenderCopy(_renderer, flagTexture, NULL, &dst);
		}
		else {
			SDL_RenderCopy(_renderer, hiddenTexture, NULL, &dst);
		}
	}
}

void Tile::Expose() {
	if (!isExposed) {
		isExposed = true;
		if (surroundedBombs == 0) {
			for (Tile* const tile : surroundedTiles) {
				tile->Expose();
			}
		}
	}
}

void Tile::Handle(SDL_MouseButtonEvent _mouseEvent) {
	if (InRect(_mouseEvent.x, _mouseEvent.y, dst)) {
		if (_mouseEvent.button == SDL_BUTTON_LEFT) {
			if (!isFlagged) {
				LOG_INFO("Tile Clicked: ({0}, {1})", dst.x / CELL_WIDTH, dst.y / CELL_HEIGHT);
				Expose();
			}
		}
		else if (_mouseEvent.button == SDL_BUTTON_RIGHT) {
			isFlagged = !isFlagged;
		}
	}
}