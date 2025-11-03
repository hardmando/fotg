#include "../include/CharacterController.h"

CharacterController::CharacterController(SDL_Rect* t) {
	target = t;
}
void CharacterController::Move(InputHandler &i) {
	i.OnKeyPress(SDL_SCANCODE_W, 
									[this]() {
										target->y -= 5;
								 	}
								 );
i.OnKeyPress(SDL_SCANCODE_S, 
									[this]() {
										target->y += 5;
								 	}
								 );
i.OnKeyPress(SDL_SCANCODE_D, 
									[this]() {
										target->x += 5;
								 	}
								 );
i.OnKeyPress(SDL_SCANCODE_A, 
									[this]() {
										target->x -= 5;
								 	}
								 );

}

