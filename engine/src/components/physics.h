#ifndef EXSUL_ENGINE_PHYSICS_COMPONENT_H
#define EXSUL_ENGINE_PHYSICS_COMPONENT_H

#include <cstdint>

struct PhysicsBody {
	float velocity_x, velocity_y;
	float acceleration_x, acceleration_y;

	float bound_width, bound_height;
	float bound_offset_x, bound_offset_y;

	bool is_static;
	bool has_gravity;
	uint32_t collision_layer;
	uint32_t collision_mask;
};

inline PhysicsBody makeDynamicBody(float w, float h) {
	return PhysicsBody{
		0.0f, 0.0f,
		0.0f, 0.0f,
		w, h, 
		0.0f, 0.0f, 
		false, 
		true, 
		0xFFFFFFFF,
		0xFFFFFFFF
	};
}

#endif //EXSUL_ENGINE_PHYSICS_COMPONENT_H
