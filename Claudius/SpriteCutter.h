#pragma once

#include "Sprite.h"
#include "Image.h"
#include "ResourceManager.h"
#include <vector>

class SpriteCutter
{
static ResourceManager* resource;
public:
	static ResourceManager* GetResourceManager() { return resource; }
	static void SetResourceManager(ResourceManager& r) { resource = &r; }
	static std::vector<Sprite*> GetSprites(int count, Image& sheet);
};
