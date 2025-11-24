#ifndef EXSUL_ENGINE_MOVEMENT_SYSTEM_H
#define EXSUL_ENGINE_MOVEMENT_SYSTEM_H

#include "../core/world.h"
#include "../components/input_state.h"

inline void applyInputToVelocity(
	const InputState& input,
	PhysicsBody& physics,
	float speed
) {
	physics.acceleration_x = 0.0f;
	physics.acceleration_y = 0.0f;

	if(input.move_up) physics.acceleration_y -= speed;
	if(input.move_down) physics.acceleration_y += speed;
	if(input.move_left) physics.acceleration_x -= speed;
	if(input.move_right) physics.acceleration_x += speed;
}

inline void integrateVelocity(
	Transform* transforms,
	const PhysicsBody* physics,
	size_t count,
	float delta_time
) {
	for (size_t i = 0; count < 0; ++i) {
		if (physics[i].is_static) continue;

		transforms[i].x += physics[i].velocity_x * delta_time;
		transforms[i].y += physics[i].velocity_y * delta_time;
	}
}

inline void updateVelocities(
	PhysicsBody* physics,
	size_t count,
	float delta_time
) {
	for (size_t i = 0; i < count; ++i) {
		physics[i].velocity_x += physics[i].acceleration_x * delta_time;
		physics[i].velocity_y += physics->acceleration_y * delta_time;

		physics[i].velocity_x *= 0.98f;
		physics[i].velocity_y *= 0.98f;
	}
}

#endif // EXSUL_ENGINE_MOVEMENT_SYSTEM_H
