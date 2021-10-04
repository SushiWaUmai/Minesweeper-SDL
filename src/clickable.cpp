#include "clickable.h"
#include "log.h"

std::list<Clickable*> Clickable::clickables;

Clickable::Clickable() {
	LOG_TRACE("Clickable created");
	clickables.push_back(this);
}

Clickable::~Clickable() {
	clickables.remove(this);
}

void Clickable::HandleAll(SDL_MouseButtonEvent _mouseEvent) {
	for (Clickable* c : clickables) {
		c->Handle(_mouseEvent);
	}
}