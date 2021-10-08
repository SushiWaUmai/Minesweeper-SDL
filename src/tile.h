#pragma once
#include <SDL.h>
#include <forward_list>
#include "renderable.h"
#include "clickable.h"

class Tile : public Renderable, public Clickable {
public:
	static void Init();
	static SDL_Texture* tileTextures[9];
	static SDL_Texture* hiddenTexture;
	static SDL_Texture* mineTexture;
	static SDL_Texture* explodedMineTexture;
	static SDL_Texture* Tile::flagTexture;

	Tile() = default;
	Tile(int x, int y);
	void Render(SDL_Renderer* _renderer) override;
	void Handle(SDL_MouseButtonEvent _mouseEvent) override;
	void Expose();
	void Flag();
	inline bool IsMine() { return surroundedBombs == -1; }

	std::forward_list<Tile*> surroundedTiles;
	int surroundedBombs = 0;
private:
	SDL_Rect dst;
	SDL_Texture* sprite;
	bool isExposed = false;
	bool isFlagged = false;
};
