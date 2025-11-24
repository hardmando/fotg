#ifndef EXSUL_ENGINE_TEXTURE_CACHE_H
#define EXSUL_ENGINE_TEXTURE_CACHE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <cstdint>

struct TextureInfo {
	int width;
	int height;
	SDL_PixelFormatEnum format;
};

struct TextureCache {
	std::vector<SDL_Texture*> textures;
	std::vector<TextureInfo> texture_info;
	std::unordered_map<std::string, uint32_t> path_to_id;
	std::vector<uint32_t> free_ids;
	SDL_Renderer* renderer;
};

inline TextureCache initTextureCache(SDL_Renderer* renderer) {
	TextureCache cache;
	cache.renderer = renderer;
	cache.textures.reserve(256);
	cache.texture_info.reserve(256);

	return cache;
}

inline uint32_t loadTexture(TextureCache& cache, const char* path) {
	auto it = cache.path_to_id.find(path);
	if (it != cache.path_to_id.end()) {
		return it->second;
	}

	SDL_Surface* surface = IMG_Load(path);
	if (!surface) {
		return UINT32_MAX;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(cache.renderer, surface);
	TextureInfo info;
	info.width = surface->w;
	info.height = surface->h;
	info.format = static_cast<SDL_PixelFormatEnum>(surface->format->format);
	SDL_FreeSurface(surface);

	if(!texture) {
		return UINT32_MAX;
	}

	uint32_t id;
	if(!cache.free_ids.empty()) {
		id = cache.free_ids.back();
		cache.free_ids.pop_back();

		cache.textures[id] = texture;
		cache.texture_info[id] = info;
	} else {
		id = static_cast<uint32_t>(cache.textures.size());
		cache.textures.push_back(texture);
		cache.texture_info.push_back(info);
	}

	cache.path_to_id[path] = id;
	return id;
}

inline SDL_Texture* getTexture(const TextureCache& cache, uint32_t id) {
	if (id >= cache.textures.size()) {
		return nullptr;
	}
	return cache.textures[id];
}

inline const TextureInfo* getTextureInfo(const TextureCache& cache, uint32_t id) {
	if (id >= cache.texture_info.size()) {
		return nullptr;
	}
	return &cache.texture_info[id];
}

inline void unloadTexture(const TextureCache& cache, uint32_t id) {
	if (id >= cache.textures.size() || cache.textures[id] == nullptr) {
		return;
	}

	SDL_DestroyTexture(cache.textures[id]);
	cache.textures[id] = nullptr;

	cache.free_ids.push_back(id);

	for(auto it = cache.path_to_id.begin(); it != cache.path_to_id.end(); ++it) {
		if (it->second == id) {
			cache.path_to_id.erase(it);
			break;
		}
	}
}

inline void destroyTextureCache(TextureCache& cache) {
	for (SDL_Texture* texture : cache.textures) {
		if (texture) {
			SDL_DestroyTexture(texture);
		}
	}

	cache.textures.clear();
	cache.texture_info.clear();
	cache.path_to_id.clear();
	cache.free_ids.clear();
}

inline size_t getTextureCount(const TextureCache& cache) {
	return cache.textures.size() - cache.free_ids.size();
}

inline size_t getVRAMUsage(const TextureCache& cache) {
	size_t total = 0;

	for (size_t i = 0; i < cache.textures.size(); ++i) {
		if (cache.textures[i]) {
      const TextureInfo& info = cache.texture_info[i];
      int bytes_per_pixel = 4;  // Most common is RGBA
      switch (info.format) {
      	case SDL_PIXELFORMAT_RGB888:
         case SDL_PIXELFORMAT_BGR888:
         	bytes_per_pixel = 3;
          break;
         case SDL_PIXELFORMAT_RGB565:
         case SDL_PIXELFORMAT_RGBA4444:
          bytes_per_pixel = 2;
         	break;
			}
			total += info.width * info.height * bytes_per_pixel;
		}
	}
	return total;
}

inline void reloadAllTextures(TextureCache& cache) {
  auto paths = cache.path_to_id;
  for (SDL_Texture* texture : cache.textures) {
    if (texture) {
      SDL_DestroyTexture(texture);
	  }
  }
  for (const auto& [path, id] : paths) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface) {
	    SDL_Texture* texture = SDL_CreateTextureFromSurface(cache.renderer, surface);
      cache.textures[id] = texture;
      cache.texture_info[id].width = surface->w;
      cache.texture_info[id].height = surface->h;
      cache.texture_info[id].format = static_cast<SDL_PixelFormatEnum>(surface->format->format);
      SDL_FreeSurface(surface);
    }
  }
}

#endif // EXSUL_ENGINE_TEXTURE_CACHE_H
