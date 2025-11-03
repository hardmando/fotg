#ifndef EXSUL_ENGINE_CHARACTER_CONTROLLER_H
#define EXSUL_ENGINE_CHARACTER_CONTROLLER_H

#include <SDL2/SDL.h>
#include "../include/InputHandler.h"

class CharacterController {
public:
	CharacterController(SDL_Rect* t);
	void Move(InputHandler &i);
private:
	SDL_Rect* target;
};

#endif // EXSUL_ENGINE_CHARACTER_CONTROLLER_H
