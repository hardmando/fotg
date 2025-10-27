#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TextureLoader {
public:
	TextureLoader();
	SDL_Texture* loadTexture(SDL_Renderer* renderer, const char *file);
};
