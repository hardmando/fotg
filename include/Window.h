#include <SDL2/SDL.h>
#include <iostream>

class Window {
public:
	Window();
	SDL_Window* window;
	SDL_Renderer* renderer;
private:
	void initWindow();
	void initRenderer(SDL_Window* window);

};
