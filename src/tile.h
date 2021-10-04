#pragma once
#include "SDL.h"
#include "renderable.h"
#include "clickable.h"

class Tile : public Renderable, public Clickable {
public:
	static void Init(SDL_Renderer* _renderer);
	static SDL_Texture* tileTextures[8];
	static SDL_Texture* hiddenTexture;
	static SDL_Texture* bombTexture;

	Tile() = default;
	Tile(int x, int y);
	void Render(SDL_Renderer* _renderer) override;
	void Handle(SDL_MouseButtonEvent _mouseEvent) override;
	inline void Expose() { isExposed = true; }
	inline void Flag() { isFlagged = true; }

private:
	SDL_Rect dst;
	int surroundedBombs = 0;
	bool isExposed = false;
	bool isFlagged = false;
};