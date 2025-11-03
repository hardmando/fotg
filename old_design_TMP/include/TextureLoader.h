#ifndef EXSUL_ENGINE_TEXTURE_LOADER_H
#define EXSUL_ENGINE_TEXTURE_LOADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TextureLoader {
public:
	TextureLoader();
	SDL_Texture* loadTexture(SDL_Renderer* renderer, const char *file);
};

#endif // EXSUL_ENGINE_TEXTURE_LOADER_H
