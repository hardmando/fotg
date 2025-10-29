#include <SDL2/SDL.h>
#include "../include/Collision.h"

class Entity {
public:
	Entity();
	Entity(SDL_Rect* r, const char *s);

	void setRect(SDL_Rect* r);
	SDL_Rect* getRect();

	void setSprite(const char *s);
	const char* getSprite();

	void setCollider(Collision* c);
	Collision* getCollider();

	Collision* collider;
private:
	SDL_Rect* rect;
	const char *sprite;
};
