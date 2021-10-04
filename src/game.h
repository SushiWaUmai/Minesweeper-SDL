#pragma once
#include <tuple>
#include "SDL.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

#define GAME_WIDTH 8
#define GAME_HEIGHT 8

#define CELL_WIDTH SCREEN_WIDTH / GAME_WIDTH
#define CELL_HEIGHT SCREEN_HEIGHT / GAME_HEIGHT

class Game {
public:
	void StartGame();
	void StartUpdate();
	void Terminate();

private:
	void HandleEvents();
	SDL_Renderer* renderer;
	SDL_Window* window;
};
