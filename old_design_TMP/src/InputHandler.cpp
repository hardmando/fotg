#include "../include/InputHandler.h"

InputHandler::InputHandler() {
	state = SDL_GetKeyboardState(NULL);
}

void InputHandler::OnKeyPress(SDL_Scancode key, std::function<void()> callback) {
	
	if(state[key]) {
		callback();
	}
}

void InputHandler::OnKeyHold() {}

void InputHandler::Update() {
	state = SDL_GetKeyboardState(NULL);
}

