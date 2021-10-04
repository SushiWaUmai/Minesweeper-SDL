#pragma once
#include <tuple>
#include "SDL.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

#define GAME_WIDTH 8
#define GAME_HEIGHT 8

#define CELL_WIDTH SCREEN_WIDTH / GAME_WIDTH
#define CELL_HEIGHT SCREEN_HEIGHT / GAME_HEIGHT

std::tuple<SDL_Window*, SDL_Renderer*> Minesweeper_StartGame();
void Minesweeper_Update(SDL_Renderer* _renderer);
void Minesweeper_Terminate(SDL_Window* _window);
