#include <iostream>
#include "game.h"
#include "log.h"
#include "tile.h"
#include "utils.h"
#include "renderable.h"
#include "clickable.h"

void Game::StartGame() {

	LOG_TRACE("Initializing SDL...");
	int sdlInitResult = SDL_Init(SDL_INIT_EVERYTHING);
	LOG_ASSERT(!sdlInitResult, "Failed to create SDL Window");

	LOG_TRACE("Creating SDL Window...");
	window = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	LOG_ASSERT(window, "Failed to create SDL Window");

	LOG_TRACE("Creating SDL Renderer...");
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	LOG_ASSERT(renderer, "Failed to create SDL renderer");

	LOG_TRACE("Initializing Minesweeper Tiles...");
	Tile::Init(renderer);
	for (int i = 0; i < GAME_WIDTH * GAME_HEIGHT; i++) {
		tiles[i] = Tile(i % GAME_WIDTH, i / GAME_WIDTH);
	}

	srand(time(NULL));
	for(int i = 0, j = 0; i < 10; j++) {
		float val = ((float)rand() / (RAND_MAX));
		if (val < 0.5) {
			tiles[j % (GAME_WIDTH * GAME_HEIGHT)].surroundedBombs = -1;
			i++;
		}
	}
}

void Game::StartUpdate() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	while (isRunning) {
		HandleEvents();
		Render();
	}
}

void Game::Terminate() {
	LOG_INFO("Terminating Program...");
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::Render() {
	SDL_RenderClear(renderer);
	Renderable::RenderAll(renderer);
	SDL_RenderPresent(renderer);
}

void Game::HandleEvents() {
	while (SDL_PollEvent(&e) != 0) {
		switch (e.type) {
		case SDL_QUIT:
			isRunning = false;
		case SDL_MOUSEBUTTONDOWN:
			Clickable::HandleAll(e.button);
		}
	}
}