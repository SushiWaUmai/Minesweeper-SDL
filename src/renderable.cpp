#include "renderable.h"
#include "log.h"

std::list<Renderable*> Renderable::renderables;

Renderable::Renderable() {
	LOG_TRACE("Renderable created");
	renderables.push_back(this);
}

Renderable::~Renderable() {
	renderables.remove(this);
}

void Renderable::RenderAll(SDL_Renderer* _renderer) {
	for (Renderable* r : renderables) {
		r->Render(_renderer);
	}
}