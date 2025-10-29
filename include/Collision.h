#include <SDL2/SDL.h>

class Collision {
public:
	Collision();
	Collision(SDL_Rect* r);

	void setRect(SDL_Rect* r);
	SDL_Rect* getRect();

private:
	SDL_Rect* rect;
};
