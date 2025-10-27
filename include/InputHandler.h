#include <SDL2/SDL.h>
#include <functional>
#include <iostream>

class InputHandler {
public:
	InputHandler();
	void OnKeyPress(SDL_Scancode key, std::function<void()> callback);
	void OnKeyHold();
	void Update();
	void Log(SDL_Scancode key);
private:
	const Uint8* state;
};
