#include "../include/TextureLoader.h"

TextureLoader::TextureLoader() {}

SDL_Texture* TextureLoader::loadTexture(SDL_Renderer* renderer, const char *file) {
	SDL_Surface* surface = IMG_Load(file);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

