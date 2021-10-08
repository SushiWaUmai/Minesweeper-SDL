#include "tile.h"
#include "log.h"
#include "utils.h"
#include "game.h"
#include "assetloader.h"
#include <sstream>

SDL_Texture* Tile::tileTextures[9];
SDL_Texture* Tile::hiddenTexture;
SDL_Texture* Tile::mineTexture;
SDL_Texture* Tile::explodedMineTexture;
SDL_Texture* Tile::flagTexture;

void Tile::Init()
{
	for (uint32_t i = 0; i <= 8; i++) {
		std::stringstream ss;
		ss << "res/tile" << i << ".bmp";

		tileTextures[i] = AssetLoader::LoadTexture(ss.str().c_str());
	}

	hiddenTexture = AssetLoader::LoadTexture("res/tile_hidden.bmp");
	mineTexture = AssetLoader::LoadTexture("res/mine.bmp");
	flagTexture = AssetLoader::LoadTexture("res/flag.bmp");
	explodedMineTexture = AssetLoader::LoadTexture("res/mine_exploded.bmp");
}

Tile::Tile(int x, int y) {
	dst.x = x * CELL_WIDTH;
	dst.y = y * CELL_HEIGHT;
	dst.w = CELL_WIDTH;
	dst.h = CELL_HEIGHT;
	sprite = hiddenTexture;
}

void Tile::Render(SDL_Renderer* _renderer) {
	SDL_RenderCopy(_renderer, sprite, NULL, &dst);
}

void Tile::Expose() {
	if (!isExposed) {
		isExposed = true;

		if (IsMine()) {
			sprite = explodedMineTexture;
			LOG_INFO("Game Over");
		}
		else {
			sprite = tileTextures[surroundedBombs];
		}

		if (surroundedBombs == 0) {
			for (Tile* const tile : surroundedTiles) {
				tile->Expose();
			}
		}
	}
}

void Tile::Flag() {
	isFlagged = !isFlagged;
	sprite = isFlagged ? flagTexture : hiddenTexture;
}

void Tile::Handle(SDL_MouseButtonEvent _mouseEvent) {
	if (InRect(_mouseEvent.x, _mouseEvent.y, dst)) {
		if (_mouseEvent.button == SDL_BUTTON_LEFT) {
			if (!isFlagged) {
				LOG_TRACE("Tile Clicked: ({0}, {1})", dst.x / CELL_WIDTH, dst.y / CELL_HEIGHT);
				Expose();
			}
		}
		else if (_mouseEvent.button == SDL_BUTTON_RIGHT) {
			if (!isExposed) {
				Flag();
			}
		}
	}
}