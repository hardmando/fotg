#ifndef EXSUL_ENGINE_INPUT_STATE_H
#define EXSUL_ENGINE_INPUT_STATE_H

#include <cstdint>
#include <cmath>

struct InputState {
	bool move_up;
	bool move_down;
	bool move_left;
	bool move_right;
	bool jump;
	bool action;
	bool cancel;

	int32_t mouse_x;
	int32_t mouse_y;
	int32_t mouse_delta_x;
	int32_t mouse_delta_y;

	bool mouse_middle;
	bool mouse_left;
	bool mouse_right;

	int32_t scroll_delta;

	bool shift;
	bool ctrl;
	bool alt;

	bool jump_pressed;
	bool jump_released;
	bool action_pressed;
	bool action_released;
};

inline InputState makeInputState() {
	return InputState{
		false, false, false, false, // movement
		false, false, false, 				// jump, action, cancel
		0, 0, 0, 0, 								// mouse movement and mouse delta
		false, false, false, 				// mouse buttons
		0, 													// scroll
		false, false, false, 				// modifier buttons
		false, false, false, false 	// frame edge events
	};
}

inline InputState calculatEdges(const InputState& current, const InputState& previous) {
	InputState result = current;

	result.jump_pressed = current.jump && !previous.jump;
	result.jump_released = !current.jump && previous.jump;
	result.action_pressed = current.action && !previous.action;
	result.action_released = !current.action && previous.action;
	
	return result;
}

inline void getMovementDirection(const InputState& input, float& x_axis, float& y_axis) {
	x_axis = 0.0f;
	y_axis = 0.0f;

	if (input.move_left) x_axis -= 1.0f;
	if (input.move_right) x_axis += 1.0f;
	if (input.move_up) y_axis -= 1.0f;
	if (input.move_down) y_axis += 1.0f;

	if (x_axis != 0 && y_axis != 0) {
		float magnitude = sqrtf(x_axis * x_axis + y_axis * y_axis);
		x_axis /= magnitude;
		y_axis /= magnitude;
	}
}

inline bool hasMovementInput(const InputState& input) {
	return input.move_up || input.move_down || input.move_left || input.move_right;
}

inline bool hasActionInput(const InputState& input) {
	return input.jump || input.action || input.cancel;
}

inline uint32_t packInputBits(const InputState& input) {
	uint32_t bits = 0;

	if (input.move_up) bits |= (1 << 0);
	if (input.move_down) bits |= (1 << 1);
	if (input.move_left) bits |= (1 << 2);
	if (input.move_right) bits |= (1 << 3);
	if (input.jump) bits |= (1 << 4);
	if (input.action) bits |= (1 << 5);
	if (input.cancel) bits |= (1 << 6);
	if (input.mouse_left) bits |= (1 << 7);
	if (input.mouse_right) bits |= (1 << 8);
	if (input.mouse_middle) bits |= (1 << 9);
	if (input.shift) bits |= (1 << 10);
	if (input.ctrl) bits |= (1 << 11);
	if (input.alt) bits |= (1 << 12);
	if (input.jump_pressed) bits |= (1 << 13);
	if (input.jump_released) bits |= (1 << 14);
	if (input.action_pressed) bits |= (1 << 15);
	if (input.action_released) bits |= (1 << 16);

	return bits;
}

inline void unpackInputBits(InputState& input, uint32_t bits) {
	input.move_up = bits & (1 << 0);
	input.move_down = bits & (1 << 1);
	input.move_left = bits & (1 << 2);
	input.move_right = bits & (1 << 3);
	input.jump = bits & (1 << 4);
	input.action = bits & (1 << 5);
	input.cancel = bits & (1 << 6);
	input.mouse_left = bits & (1 << 7);
	input.mouse_right = bits & (1 << 8);
	input.mouse_middle = bits & (1 << 9);
	input.shift = bits & (1 << 10);
	input.ctrl = bits & (1 << 11);
	input.alt = bits & (1 << 12);
	input.jump_pressed = bits & (1 << 13);
	input.jump_released = bits & (1 << 14);
	input.action_pressed = bits & (1 << 15);
	input.action_released = bits & (1 << 16);
}

#endif // EXSUL_ENGINE_INPUT_STATE_H
