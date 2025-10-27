#include "Window.h"
#include "TextureLoader.h"

int main(int argc, char* argv[]) {
	Window w;
	TextureLoader t_loader;

	bool running = true;
	SDL_Event event;


	SDL_Texture* texture = t_loader.loadTexture(w.renderer, "../sprite.png");

	while(running) {
		while(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}
		
		SDL_SetRenderDrawColor(w.renderer, 0, 0, 0, 255);
		
		SDL_Rect rect = { 350, 250, 100, 100 };
    	SDL_RenderClear(w.renderer);
    	SDL_RenderPresent(w.renderer); 

		SDL_Delay(16);
	}

	SDL_DestroyWindow(w.window);
	SDL_Quit();

	return 0;
}
