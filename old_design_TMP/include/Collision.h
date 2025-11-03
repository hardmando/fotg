#ifndef EXSUL_ENGINE_COLLISION_H
#define EXSUL_ENGINE_COLLISION_H

#include <SDL2/SDL.h>
#include <vector>

class Collision {
public:
	Collision();
	Collision(SDL_Rect* r);

	void setRect(SDL_Rect* r);
	SDL_Rect* getRect();
	
	std::vector<Collision>* getCollisions();
private:
	SDL_Rect* rect;
	std::vector<Collision>* collisions;
};

#endif // EXSUL_ENGINE_COLLISION_H
