#include "../include/Entity.h"

Entity::Entity(){
	Entity::rect = nullptr;
	Entity::sprite = nullptr;
	collider = new Collision();
}

Entity::Entity(int posX, int posY, int width, int height, const char *s) {
	Entity::rect = new SDL_Rect{ posX, posY, width, height };
	Entity::position = {posX, posY};
	Entity::size = {width, height};
	Entity::sprite = s;
	collider = new Collision(Entity::rect);
}

SDL_Rect* Entity::getRect() { return Entity::rect; }

void Entity::setSprite(const char *s) { Entity::sprite = s; }
const char* Entity::getSprite() { return Entity::sprite; }

void Entity::setCollider(Collision* c) { Entity::collider = c; }
Collision* Entity::getCollider() { return Entity::collider; }

void Entity::setPosition(int posX, int posY) {
	Entity::position = {posX, posY};
}
std::pair<int, int> Entity::getPosition() { return Entity::position; }

void Entity::setSize(int width, int height) {
	Entity::size = {width, height};
}
std::pair<int, int> Entity::getSize() { return Entity::size; }
