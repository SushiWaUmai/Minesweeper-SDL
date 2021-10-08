#include <iostream>
#include "game.h"
#include "log.h"
#include "tile.h"
#include "utils.h"
#include "renderable.h"
#include "clickable.h"
#include "assetloader.h"

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

	AssetLoader::Init(renderer);

	LOG_TRACE("Initializing Minesweeper Tiles...");
	Tile::Init();
	for (uint32_t i = 0; i < GAME_WIDTH * GAME_HEIGHT; i++) {
		tiles[i] = Tile(i % GAME_WIDTH, i / GAME_WIDTH, [&]() { GameOver(); });
	}

	srand((uint32_t)time(NULL));
	for (int i = 0, j = 0; i < GAME_BOMBS; j++) {
		float val = ((float)rand() / (RAND_MAX));
		if (val < 1.0f / (GAME_WIDTH * GAME_HEIGHT)) {
			tiles[j % (GAME_WIDTH * GAME_HEIGHT)].surroundedBombs = -1;
			i++;
		}
	}

	for (int y = 0; y < GAME_HEIGHT; y++) {
		for (int x = 0; x < GAME_WIDTH; x++) {
			if (tiles[y * GAME_HEIGHT + x].surroundedBombs == -1)
				continue;

			int bombs = 0;
			for (int dx = x - 1; dx <= x + 1; dx++) {
				for (int dy = y - 1; dy <= y + 1; dy++) {
					if (dx >= 0 && dx < GAME_WIDTH && dy >= 0 && dy < GAME_HEIGHT) {
						if (dx != x || dy != y) {
							if (tiles[dy * GAME_HEIGHT + dx].surroundedBombs == -1)
								bombs++;
							tiles[y * GAME_HEIGHT + x].surroundedTiles.push_front(&tiles[dy * GAME_HEIGHT + dx]);
						}
					}
				}
			}
			tiles[y * GAME_HEIGHT + x].surroundedBombs = bombs;
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
	AssetLoader::Terminate();

	SDL_DestroyRenderer(renderer);
	LOG_TRACE("Renderer Destroyed");

	SDL_DestroyWindow(window);
	LOG_TRACE("Window Destroyed");

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
			break;
		case SDL_MOUSEBUTTONDOWN:
			Clickable::HandleAll(e.button);
			break;
		}
	}
}

void Game::GameOver() {
	LOG_INFO("Game Over");
	for (Tile& t : tiles) {
		t.CheckTile();
	}
}