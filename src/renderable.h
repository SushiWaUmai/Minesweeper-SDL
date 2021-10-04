#pragma once
#include "SDL.h"
#include <list>

class Renderable {
public:
	static void RenderAll(SDL_Renderer* _renderer);

protected:
	virtual void Render(SDL_Renderer* _renderer) = 0;
	Renderable();
	~Renderable();

private:
	static std::list<Renderable*> renderables;
};