#include <iostream>
#include "game.h"
#include "log.h"
#include "tile.h"
#include "utils.h"

void Game::StartGame() {
	int sdlInitResult = SDL_Init(SDL_INIT_EVERYTHING);
	LOG_ASSERT(!sdlInitResult, "Failed to create SDL Window");

	window = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	LOG_ASSERT(window, "Failed to create SDL Window");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	LOG_ASSERT(renderer, "Failed to create SDL renderer");

	Tile::Init(renderer);
}

void Game::StartUpdate() {
	SDL_Event e;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	Tile tiles[GAME_WIDTH * GAME_HEIGHT];

	for (int i = 0; i < GAME_WIDTH * GAME_HEIGHT; i++) {
		tiles[i] = Tile(i % GAME_WIDTH, i / GAME_WIDTH);
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

		SDL_RenderClear(renderer);

		for (int i = 0; i < GAME_WIDTH * GAME_HEIGHT; i++) {
			tiles[i].Render(renderer);
		}

		SDL_RenderPresent(renderer);
	}
}

void Game::Terminate() {
	LOG_INFO("Terminating Program...");
	SDL_DestroyWindow(window);
	SDL_Quit();
}