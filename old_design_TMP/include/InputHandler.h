#ifndef EXSUL_ENGINE_INPUT_HANDLER_H
#define EXSUL_ENGINE_INPUT_HANDLER_H

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

#endif // EXSUL_ENGINE_INPUT_HANDLER_H
