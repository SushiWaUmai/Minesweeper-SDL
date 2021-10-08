#pragma once
#include <iostream>
#include <unordered_map>
#include <SDL.h>

class AssetLoader {
public:
	static SDL_Renderer* renderer;
	static void Init(SDL_Renderer* renderer);
	static void Terminate();

	static SDL_Texture* LoadTexture(const char* filePath);

private:
	static std::unordered_map<const char*, SDL_Texture*> textureAssets;
};
