#include "tile.h"
#include "log.h"
#include "utils.h"
#include "game.h"
#include "assetloader.h"
#include <sstream>

SDL_Texture* Tile::tileTextures[9];
SDL_Texture* Tile::hiddenTexture;
SDL_Texture* Tile::bombTexture;
SDL_Texture* Tile::flagTexture;

void Tile::Init()
{
	for (uint32_t i = 0; i <= 8; i++) {
		std::stringstream ss;
		ss << "res/tile" << i << ".bmp";

		tileTextures[i] = AssetLoader::LoadTexture(ss.str().c_str());
	}

	hiddenTexture = AssetLoader::LoadTexture("res/hidden.bmp");
	bombTexture = AssetLoader::LoadTexture("res/bomb.bmp");
	flagTexture = AssetLoader::LoadTexture("res/flag.bmp");
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