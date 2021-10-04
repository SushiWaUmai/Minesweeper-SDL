#pragma once
#include <list>
#include "SDL.h"

class Clickable {
public:
	static void HandleAll(SDL_MouseButtonEvent _mouseEvent);

protected:
	virtual void Handle(SDL_MouseButtonEvent _mouseEvent) = 0;
	Clickable();
	~Clickable();

private:
	static std::list<Clickable*> clickables;
};