#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "SDL.h"
#include "game.h"
#include "log.h"

int main(int argc, char** args) {
	(void)argc;
	(void)args;

	LOG_SET_LEVEL(LOG_LEVEL_TRACE);

	Game game = Game();
	game.Run();

	return EXIT_SUCCESS;
}
