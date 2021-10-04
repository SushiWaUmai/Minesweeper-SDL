#include <iostream>
#include "SDL.h"
#include "game.h"
#include "log.h"

int main(int argc, char** args) {
	(void)argc;
	(void)args;

	Game game = Game();
	game.StartGame();
	game.StartUpdate();
	game.Terminate();

	return EXIT_SUCCESS;
}