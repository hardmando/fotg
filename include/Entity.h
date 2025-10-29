#include <SDL2/SDL.h>
#include "../include/Collision.h"

class Entity {
public:
	Entity();
	Entity(int posX, int posY, int width, int height, const char *s);

	void setPosition(int posX, int posY);
	std::pair<int, int> getPosition();
	
	void setSize(int width, int height);
	std::pair<int, int> getSize();

	SDL_Rect* getRect();

	void setSprite(const char *s);
	const char* getSprite();

	void setCollider(Collision* c);
	Collision* getCollider();

	Collision* collider;
private:
	SDL_Rect* rect;
	const char *sprite;
	std::pair<int, int> position;
	std::pair<int, int> size;
};
