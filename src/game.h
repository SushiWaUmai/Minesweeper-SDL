#pragma once
#include <tuple>
#include "SDL.h"

std::tuple<SDL_Window*, SDL_Renderer*> Minesweeper_StartGame();
void Minesweeper_Update(SDL_Renderer* _renderer);
void Minesweeper_Terminate(SDL_Window* _window);
