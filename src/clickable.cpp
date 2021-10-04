#include "clickable.h"
#include "log.h"

void Clickable::HandleAll(SDL_MouseButtonEvent _mouseEvent) {
	for (Clickable* c : instances) {
		c->Handle(_mouseEvent);
	}
}
