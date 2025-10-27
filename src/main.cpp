#include "../include/Window.h"
#include "../include/TextureLoader.h"
#include "../include/CharacterController.h"
#include <iostream>

int main(int argc, char* argv[]) {
	Window w;
	TextureLoader t_loader;
	InputHandler input;
	SDL_Rect rect = { 350, 250, 100, 100 };
	CharacterController controller = CharacterController(rect);
	
	bool running = true;
	SDL_Event event;


	SDL_Texture* texture = t_loader.loadTexture(w.renderer, "../assets/mario.png");

	while(running) {
		controller.Move(input);
		while(SDL_PollEvent(&event)) {
			input.Update();
		
			input.OnKeyPress(SDL_SCANCODE_SPACE, []() { 
				std::cout << SDL_SCANCODE_SPACE << std::endl;
			});
			
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}
		
		SDL_SetRenderDrawColor(w.renderer, 0, 0, 0, 255);
		

    SDL_RenderClear(w.renderer);
		SDL_RenderCopy(w.renderer, texture, NULL, &rect);
    SDL_RenderPresent(w.renderer); 

		SDL_Delay(16);
	}

	SDL_DestroyWindow(w.window);
	SDL_Quit();

	return 0;
}
