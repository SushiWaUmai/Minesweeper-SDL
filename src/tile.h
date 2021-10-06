#pragma once
#include "SDL.h"
#include "renderable.h"
#include "clickable.h"
#include <forward_list>

class Tile : public Renderable, public Clickable {
public:
	static void Init(SDL_Renderer* _renderer);
	static SDL_Texture* tileTextures[9];
	static SDL_Texture* hiddenTexture;
	static SDL_Texture* bombTexture;
	static SDL_Texture* Tile::flagTexture;

	Tile() = default;
	Tile(int x, int y);
	void Render(SDL_Renderer* _renderer) override;
	void Handle(SDL_MouseButtonEvent _mouseEvent) override;
	void Expose();

	std::forward_list<Tile*> surroundedTiles;
	int surroundedBombs = 0;
private:
	SDL_Rect dst;
	bool isExposed = false;
	bool isFlagged = false;
};