#ifndef EXSUL_ENGINE_RENDERER_H
#define EXSUL_ENGINE_RENDERER_H

#include <SDL2/SDL.h>
#include "../core/world.h"

struct RenderContext {
	SDL_Window* window;
	SDL_Renderer* renderer;
	int screen_width;
	int screen_height;
};

RenderContext initRenderer(const char* title, int width, int height);

void destroyRenderer(RenderContext& ctx);

void render(
	RenderContext& ctx,
	const std::vector<Transform>& transforms,
	const std::vector<Sprite>& sprites,
	const std::vector<uint32_t>& entity_to_transform,
	const std::vector<uint32_t>& entity_to_sprite
);

#endif // EXSUL_ENGINE_RENDERER_H
