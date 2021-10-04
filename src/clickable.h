#pragma once
#include <list>
#include "SDL.h"
#include "listable.h"

class Clickable : public Listable<Clickable> {
public:
	static void HandleAll(SDL_MouseButtonEvent _mouseEvent);

protected:
	virtual void Handle(SDL_MouseButtonEvent _mouseEvent) = 0;
};

