#ifndef EXSUL_ENGINE_COMPONENT_ARRAYS_H
#define EXSUL_ENGINE_COMPONENT_ARRAYS_H

#include "world.h"

inline EntityHandle createEntity(World& world) {
	EntityHandle handle;
	if (!world.free_entities.empty()) {
		handle = world.free_entities.back();
		world.free_entities.pop_back();
	} else {
		handle = world.next_entity_id++;
	}

	if (handle >= world.entity_to_transform.size()) {
		world.entity_to_transform.resize(handle + 1, UINT32_MAX);
		world.entity_to_sprite.resize(handle + 1, UINT32_MAX);
		world.entity_to_physics.resize(handle + 1, UINT32_MAX);
	}
	return handle;
}

inline void addTransform(World& world, EntityHandle entity, const Transform& transform) {
	uint32_t index = world.transforms.size();
	world.transforms.push_back(transform);
	world.entity_to_transform[entity] = index;
}

inline void addSprite(World& world, EntityHandle entity, const Sprite& sprite) {
	uint32_t index = world.sprites.size();
	world.sprites.push_back(sprite);
	world.entity_to_sprite[entity] = index;
}

inline void addPhysics(World& world, EntityHandle entity, const PhysicsBody physic) {
	uint32_t index = world.physics.size();
	world.physics.push_back(physic);
	world.entity_to_physics[entity] = index;
}

inline Transform* getTransform(World& world, EntityHandle entity) {
	if (entity >= world.entity_to_transform.size()) return nullptr;
	uint32_t index = world.entity_to_transform[entity];
	if (entity == UINT32_MAX) return nullptr;
	return &world.transforms[entity];
}

#endif // EXSUL_ENGINE_COMPONENT_ARRAYS_H

