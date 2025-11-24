#ifndef EXSUL_ENGINE_INPUT_SYSTEM_H
#define EXSUL_ENGINE_INPUT_SYSTEM_H

#include <SDL2/SDL.h>
#include "../components/input_state.h"

static InputState previous_input = makeInputState();

inline InputState captureInput() {
	const Uint8* keys = SDL_GetKeyboardState(nullptr);

	int mouse_x, mouse_y;
	uint32_t mouse_buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

	int mouse_delta_x, mouse_delta_y;
	SDL_GetRelativeMouseState(&mouse_delta_x, &mouse_delta_y);

	InputState current = makeInputState();

	current.move_up = keys[SDL_SCANCODE_W];
	current.move_down = keys[SDL_SCANCODE_S];
	current.move_left = keys[SDL_SCANCODE_A];
	current.move_right = keys[SDL_SCANCODE_D];
	current.jump = keys[SDL_SCANCODE_SPACE];
	current.action = keys[SDL_SCANCODE_E];
	current.cancel = keys[SDL_SCANCODE_ESCAPE];

	current.mouse_x = mouse_x;
	current.mouse_y = mouse_y;
	current.mouse_delta_x = mouse_delta_x;
	current.mouse_delta_y = mouse_delta_y;
	current.mouse_left = mouse_buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
	current.mouse_right = mouse_buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
	current.mouse_middle = mouse_buttons & SDL_BUTTON(SDL_BUTTON_MIDDLE);

	SDL_Keymod mods = SDL_GetModState();
	current.shift = mods & KMOD_SHIFT;
	current.ctrl = mods & KMOD_CTRL;
	current.alt = mods & KMOD_ALT;
	
	InputState with_edges = calculatEdges(current, previous_input);

	previous_input = current;

	return with_edges;
}

inline void updateScrollDelta(InputState& input, const SDL_Event& event) {
	if (event.type == SDL_MOUSEWHEEL) {
		input.scroll_delta = event.wheel.y;
	}
}

inline bool processEvents(InputState& input) {
	SDL_Event event;
	input.scroll_delta = 0;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return true;
		}
		updateScrollDelta(input, event);
	}
	return false;
}

#endif // EXSUL_ENGINE_INPUT_SYSTEM_H
