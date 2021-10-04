#pragma once
#include "SDL.h"
#include "log.h"

SDL_Texture* LoadTexture(const char* filePath, SDL_Renderer* _renderer);
bool InRect(int x, int y, SDL_Rect& r);
