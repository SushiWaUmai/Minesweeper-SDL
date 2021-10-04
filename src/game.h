#pragma once
#include <tuple>
#include <functional>
#include "SDL.h"
#include "tile.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

#define GAME_WIDTH 16
#define GAME_HEIGHT 16

#define CELL_WIDTH (SCREEN_WIDTH / GAME_WIDTH)
#define CELL_HEIGHT (SCREEN_HEIGHT / GAME_HEIGHT)

class Game {
public:
	void StartGame();
	void StartUpdate();
	void Terminate();

private:
	void HandleEvents();
	void Render();

	bool isRunning = true;
	Tile tiles[GAME_WIDTH * GAME_HEIGHT];
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Event e;
};
