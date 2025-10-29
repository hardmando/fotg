#include "../include/Entity.h"

Entity::Entity(){
	Entity::rect = nullptr;
	Entity::sprite = nullptr;
	collider = new Collision();
}

Entity::Entity(SDL_Rect* r, const char *s) : rect(r){
	Entity::rect = r;
	Entity::sprite = s;
	collider = new Collision(rect);
}

void Entity::setRect(SDL_Rect* r) { Entity::rect = r; }
SDL_Rect* Entity::getRect() { return Entity::rect; }

void Entity::setSprite(const char *s) { Entity::sprite = s; }
const char* Entity::getSprite() { return Entity::sprite; }

void Entity::setCollider(Collision* c) { Entity::collider = c; }
Collision* Entity::getCollider() { return Entity::collider; }
