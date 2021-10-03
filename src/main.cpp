#include <iostream>
#include "SDL.h"

#define LOG(x) std::cout << x << std::endl

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char* args[]) {
	(void)argc;
	(void)args;

	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		LOG("SDL could not be initialized");
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_Window* window = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window) {
		LOG("Failed to create SDL Window");
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		LOG("Failed to create SDL renderer");
		SDL_Quit();
		return EXIT_FAILURE;
	}

	while (true) {
		SDL_Event e;
		SDL_WaitEvent(&e);

		if (e.type == SDL_QUIT)
			break;
	}

	SDL_Quit();

	return EXIT_SUCCESS;
}