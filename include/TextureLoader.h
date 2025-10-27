#include <SDL2_image/SDL_image.h>

class TextureLoader {
public:
	TextureLoader();
	SDL_Texture* loadTexture(SDL_Renderer* renderer, const char *file);
};
