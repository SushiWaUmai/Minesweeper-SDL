#include "assetloader.h"
#include "utils.h"
#include <sstream>

std::unordered_map<const char*, SDL_Texture*> AssetLoader::textureAssets;
SDL_Renderer* AssetLoader::renderer;

void AssetLoader::Init(SDL_Renderer* _renderer) {
	renderer = _renderer;
	LOG_TRACE("AssetLoader Initialized");
}

void AssetLoader::Terminate() {
	for (auto& [filePath, texture] : textureAssets) {
		SDL_DestroyTexture(texture);
	}
	LOG_TRACE("AssetLoader Teminated");
}

SDL_Texture* AssetLoader::LoadTexture(const char* filePath) {
	if (textureAssets[filePath]) {
		LOG_TRACE("Loaded cached texture: {0}", filePath);
		return textureAssets[filePath];
	}

	SDL_Surface* image = SDL_LoadBMP(filePath);
	LOG_ASSERT(image, "Failed to load image");

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
	LOG_ASSERT(texture, "Failed to create texture");

	SDL_FreeSurface(image);

	LOG_TRACE("Loaded texture into RAM: {0}", filePath);

	return texture;
}
