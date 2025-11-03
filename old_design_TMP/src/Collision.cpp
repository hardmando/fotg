#include "../include/Collision.h"

Collision::Collision(){
	Collision::rect = nullptr;
	Collision::collisions = new std::vector<Collision>();
}
Collision::Collision(SDL_Rect* r) {
	Collision::rect = r;
	Collision::collisions = new std::vector<Collision>();
}

void Collision::setRect(SDL_Rect* r) { Collision::rect = r; }
SDL_Rect* Collision::getRect() { return Collision::rect; }

std::vector<Collision>* Collision::getCollisions() { return Collision::collisions; }
