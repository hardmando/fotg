#ifndef EXSUL_ENGINE_WORLD_H
#define EXSUL_ENGINE_WORLD_H

#include <cstdint>
#include <vector>

#include "../components/transform.h"
#include "../components/sprite.h"
#include "../components/physics.h"

using EntityHandle = uint32_t;
constexpr EntityHandle INVALID_ENTITY = UINT32_MAX;

struct World
{
  std::vector<Transform> transforms;
  std::vector<Sprite> sprites;
  std::vector<PhysicsBody> physics;

	std::vector<uint32_t> entity_to_transform;
	std::vector<uint32_t> entity_to_sprite;
	std::vector<uint32_t> entity_to_physics;

	std::vector<EntityHandle> free_entities;
	uint32_t next_entity_id = 0;

	double delta_time;
	uint64_t frame_count;
};

#endif // EXSUL_ENGINE_WORLD_H
