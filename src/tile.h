#pragma once
#include "SDL.h"

class Tile {
public:
	static void Init(SDL_Renderer* _renderer);
	static SDL_Texture* tileTextures[8];
	static SDL_Texture* hiddenTexture;

	Tile() = default;
	void Expose();
	void Flag();
	void Render(SDL_Renderer* _renderer);

	SDL_Rect dst;
	int surroundedBombs = 0;
	bool isExposed = false;
	bool isFlagged = false;
};