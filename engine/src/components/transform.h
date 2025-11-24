#ifndef EXSUL_ENGINE_TRANSFORM_COMPONENT_H
#define EXSUL_ENGINE_TRANSFORM_COMPONENT_H

struct Transform {
	float x, y;
	float rotation;
	float scale_x, scale_y;
};

inline Transform makeTransfrom(float x, float y) {
	return Transform{x, y, 0.0f, 1.0f, 1.0f};
}

inline Transform translate(const Transform& t, float d_x, float d_y) {
	return Transform{
		t.x + d_x,
		t.y + d_y,
		t.rotation,
		t.scale_x,
		t.scale_y
	};
}

inline Transform rotate(const Transform& t, float d_rotation) {
	return Transform{
		t.x,
		t.y,
		t.rotation + d_rotation,
		t.scale_x,
		t.scale_y
	};
}

#endif // EXSUL_ENGINE_TRANSFORM_COMPONENT_H

