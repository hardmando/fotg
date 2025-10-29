#include "../include/Collision.h"

Collision::Collision(){
	Collision::rect = nullptr;
}
Collision::Collision(SDL_Rect* r) {
	Collision::rect = r;
}

void Collision::setRect(SDL_Rect* r) { Collision::rect = r; }
SDL_Rect* Collision::getRect() { return Collision::rect; }
