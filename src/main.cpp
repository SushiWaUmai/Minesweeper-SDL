#include <iostream>
#include "SDL.h"
#include "game.h"
#include "log.h"

int main(int argc, char** args) {
	(void)argc;
	(void)args;

	auto [window, renderer] = Minesweeper_StartGame();
	Minesweeper_Update(renderer);
	Minesweeper_Terminate(window);

	return EXIT_SUCCESS;
}