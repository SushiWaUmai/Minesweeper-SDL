#include <iostream>
#include "game.h"
#include "log.h"
#include "tile.h"
#include "utils.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define GAME_WIDTH 8
#define GAME_HEIGHT 8

std::tuple<SDL_Window*, SDL_Renderer*> Minesweeper_StartGame() {
	int sdlInitResult = SDL_Init(SDL_INIT_EVERYTHING);
	LOG_ASSERT(!sdlInitResult , "Failed to create SDL Window");

	SDL_Window* window = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	LOG_ASSERT(window, "Failed to create SDL Window");

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	LOG_ASSERT(renderer, "Failed to create SDL renderer");

	Tile::Init(renderer);
	return { window, renderer };
}

void Minesweeper_Update(SDL_Renderer* _renderer) {
	SDL_Event e;

	SDL_Texture* texture = LoadTexture("res/bomb.bmp", _renderer);

	SDL_Rect dst;
	dst.x = 0;
	dst.y = 0;
	dst.w = 500;
	dst.h = 500;

	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);

	Tile tiles[GAME_WIDTH * GAME_HEIGHT];

	for (int i = 0; i < GAME_WIDTH * GAME_HEIGHT; i++) {
		if (i % 5 == 0) {
			tiles[i].surroundedBombs = -1;
		}
	}

	bool running = true;
	while (running) {
		SDL_PollEvent(&e);
		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
			case SDL_QUIT:
				running = false;
			}
		}

		SDL_RenderClear(_renderer);

		for (int i = 0; i < GAME_WIDTH * GAME_HEIGHT; i++) {
			tiles[i].Render(_renderer);
		}

		SDL_RenderCopy(_renderer, texture, NULL, &dst);

		SDL_RenderPresent(_renderer);
	}
}

void Minesweeper_Terminate(SDL_Window* _window) {
	LOG_INFO("Terminating Program...");
	SDL_DestroyWindow(_window);
	SDL_Quit();
}
