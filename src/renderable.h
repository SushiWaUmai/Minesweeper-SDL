#pragma once
#include <SDL.h>
#include <list>
#include "listable.h"

class Renderable : public Listable<Renderable> {
public:
	static void RenderAll(SDL_Renderer* _renderer);

protected:
	virtual void Render(SDL_Renderer* _renderer) = 0;
};
