#include "renderer.h"
#include "texture_cache.h"
#include <algorithm>

RenderContext initRenderer(const char* title, int width, int height) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_SHOWN
	);

	SDL_Renderer* renderer = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	
	return RenderContext{window, renderer, width, height};
}

void destroyRenderer(RenderContext& ctx) {
	SDL_DestroyRenderer(ctx.renderer);
	SDL_DestroyWindow(ctx.window);
}

struct RenderCommand {
	uint32_t sprite_index;
	uint32_t transform_index;
	uint8_t layer;
};

void render(
	RenderContext& ctx,
	const std::vector<Transform>& transform,
	const std::vector<Sprite>& sprites,
	const std::vector<uint32_t>& entity_to_transform,
	const std::vector<uint32_t>& entity_to_sprite
) {
	std::vector<RenderCommand> commands;
	commands.reserve(sprites.size());

	for (size_t entity = 0; entity <  entity_to_sprite.size(); ++entity) {
		uint32_t sprite_idx = entity_to_sprite[entity];
		if (sprite_idx == UINT32_MAX) continue;

		const Sprite& sprite = sprites[sprite_idx];
		if (!sprite.visible) continue;

		uint32_t transform_idx = entity_to_transform[entity];
		if (transform_idx == UINT32_MAX) continue;
		
		commands.push_back({sprite_idx, transform_idx, sprite.layer});
	}

	std::sort(commands.begin(), commands.end(),
						[](const RenderCommand& a, const RenderCommand& b) {
					 	return a.layer < b.layer;
					 });

	SDL_SetRenderDrawColor(ctx.renderer, 0, 0, 0, 255);
	SDL_RenderClear(ctx.renderer);

	for (const RenderCommand& cmd : commands) {
		const Transform& t = transform[cmd.transform_index];
		const Sprite& s = sprites[cmd.sprite_index];

		SDL_Rect dest = {
			static_cast<int>(t.x),
			static_cast<int>(t.y),
			static_cast<int>(s.width * t.scale_x),
			static_cast<int>(s.height * t.scale_y)
		};

		SDL_Texture* texture = getTextureFromCache(s.texture_id);
		SDL_RenderCopy(ctx.renderer, texture, nullptr, &dest);
	}

	SDL_RenderPresent(ctx.renderer);
}
