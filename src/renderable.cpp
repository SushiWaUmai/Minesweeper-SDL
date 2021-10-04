#include "renderable.h"
#include "log.h"

void Renderable::RenderAll(SDL_Renderer* _renderer) {
	for (Renderable* r : instances) {
		r->Render(_renderer);
	}
}
