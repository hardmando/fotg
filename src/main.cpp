#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include "init.h"

int main(int argc, char* argv[]) {
	init::SDL_Window* window = initWindow();
	init::SDL_Renderer* renderer = initRenderer(window);

	SDL_Surface* surface = IMG_Load("sprite.png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	bool running = true;
	SDL_Event event;

	while(running) {
		while(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		
		SDL_Rect rect = { 350, 250, 100, 100 };
    	SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, &rect);
    	SDL_RenderPresent(renderer); 

		SDL_Delay(16);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
