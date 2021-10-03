#include <iostream>
#include "SDL.h"
#include "spdlog/spdlog.h"

#define LOG_TRACE(...) spdlog::trace(__VA_ARGS__)
#define LOG_INFO(...) spdlog::info(__VA_ARGS__)
#define LOG_DEBUG(...) spdlog::debug(__VA_ARGS__)
#define LOG_WARNING(...) spdlog::warn(__VA_ARGS__)
#define LOG_ERROR(...) spdlog::error(__VA_ARGS__)
#define LOG_CRITICAL(...) spdlog::critical(__VA_ARGS__)

#ifdef _WIN32
#define DEBUG_BREAK() __debugbreak()
#else
#include <signal.h>
#define raise(SIGTRAP)
#endif

#define LOG_ASSERT(check, msg)	{ if(!check) { LOG_ERROR("Assertion Failed: {0}", msg); } }

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char* args[]) {
	(void)argc;
	(void)args;

	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		LOG_ERROR("SDL could not be initialized: {0}", SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_Window* window = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window) {
		LOG_ERROR("Failed to create SDL Window: {0}", SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		LOG_ERROR("Failed to create SDL renderer: {0}", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_FAILURE;
	}

	while (true) {
		SDL_Event e;
		SDL_WaitEvent(&e);

		if (e.type == SDL_QUIT)
			break;
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}