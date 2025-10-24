#include "init.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

SDL_Window* initWindow() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
	}

	SDL_Window* window = SDL_CreateWindow(
		"SDL Window",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800, 600,
		SDL_WINDOW_SHOWN
	);
	if (window == nullptr) {
		std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}
	return window;
}

SDL_Renderer* initRenderer(SDL_Window* window) {
	SDL_Renderer* renderer = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED
	);

	return renderer;
}
