#include "../include/Window.h"
#include "../include/TextureLoader.h"
#include "../include/CharacterController.h"
#include "../include/Entity.h"
#include <iostream>

int main(int argc, char* argv[]) {
	Window w;
	TextureLoader t_loader;
	InputHandler input;
	Entity mainCharacter = Entity(350, 250, 100, 100, "../assets/marion.png");
	CharacterController controller = CharacterController(mainCharacter.getRect());
	
	bool running = true;
	SDL_Event event;


	SDL_Texture* texture = t_loader.loadTexture(w.renderer, mainCharacter.getSprite());

	while(running) {
		controller.Move(input);
		while(SDL_PollEvent(&event)) {
			input.Update();
			
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}
		
		SDL_SetRenderDrawColor(w.renderer, 0, 0, 0, 255);
		

    	SDL_RenderClear(w.renderer);
		SDL_RenderCopy(w.renderer, texture, NULL, mainCharacter.getRect());
    	SDL_RenderPresent(w.renderer); 

		SDL_Delay(16);
	}

	SDL_DestroyWindow(w.window);
	SDL_Quit();

	return 0;
}
