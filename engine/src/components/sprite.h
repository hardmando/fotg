#ifndef EXSUL_ENGINE_SPRITE_COMPONENT_H
#define EXSUL_ENGINE_SPRITE_COMPONENT_H

#include <cstdint>

struct Sprite {
	uint32_t texture_id;
	int width, height;
	uint8_t layer;

	float alpha;
	bool visible;
};

inline Sprite makeSprite(uint32_t texture_id, int w, int h, uint8_t layer = 0) {
	return Sprite{texture_id, w, h, layer, 1.0f, true};
}

#endif // EXSUL_ENGINE_SPRITE_COMPOMEMT_H
