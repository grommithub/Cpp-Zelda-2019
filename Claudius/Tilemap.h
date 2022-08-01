#pragma once

#include "RenderManager.h"
#include "SpriteCutter.h"
#include "Collider.h"
#include "Transform.h"
#include "ScreenDimentions.h"
#include "Camera.h"
#include "Color.h"
#include "CollisionManager.h"


class Tile
{
public:

	Tile(Sprite* spr, Vector2 pos);
	virtual void Render(RenderManager& renderer, bool debug);
	Sprite* GetSprite() { return sprite; };
protected:
	Sprite* sprite;
	Transform transform;
	Transform renderTransform;
};

class WallTile : public Tile
{
	Color debugColor = Color::Blue();
	void Render(RenderManager& renderer, bool debug);
	Rectangle debugRect;
public:
	Collider collider;
	WallTile(Sprite* sprite, Vector2);
};

class Tilemap
{
	int screenW; //16
	int screenH; //11
	float tileSize;
	std::vector<Tile*> palette;
	std::vector<Tile*> allTiles;
	std::vector<WallTile*> wallTiles;
	//std::vector<Tile*> waterTiles;
	std::vector<Sprite*> tileSprites;

	Image tileSet;

	Vector2 CoordsToVector2(int x, int y);
	void CreatePalette();

	void PlaceTiles();
	void PlaceTile(int x, int y, int screenX, int screenY, int index);
public:
	~Tilemap();
	Tilemap();
	void CollisionCheck(Entity* entity);
	Vector2 CoordsToVector2(int x, int y, int screenX, int screenY);
	void Render(RenderManager& renderer, bool debug);
};