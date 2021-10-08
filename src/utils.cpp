#include "utils.h"

bool InRect(int x, int y, SDL_Rect& r) {
	return (x >= r.x) && (y >= r.y) &&
		(x < r.x + r.w) && (y < r.y + r.h);
}