#include "Tilemap.h"
#include <iostream>
#include <fstream>
#include <string>

Vector2 Tilemap::CoordsToVector2(int x, int y)
{
	return Vector2(x * tileSize * SCALE, y * tileSize * SCALE + (UI_HEIGHT * SCALE));
}

Vector2 Tilemap::CoordsToVector2(int x, int y, int screenX, int screenY) //screenX & screenY are which screen you're on, on the larger world grid
{
	Vector2 pos = CoordsToVector2(x + (screenX * screenW), y + (screenY * screenH));
	return pos;
}

void Tilemap::CollisionCheck(Entity* entity)
{
	for (int i = 0; i < wallTiles.size(); i++)
	{
		if (CollisionManager::CheckCollision(entity->GetCollider(), wallTiles[i]->collider))
		{
			entity->OnTilemapCollide(wallTiles[i]->collider.rect);
			return;
		}
	}
}

Tilemap::Tilemap() : screenH(11), screenW(16), tileSize(16.0f)
{
	CreatePalette();
	PlaceTiles();
}

Tilemap::~Tilemap()
{
	for (Tile* tile : allTiles)
		delete tile;
	for (WallTile* wall : wallTiles)
		delete wall;
	for (Tile* tile : palette)
		delete tile;
	for (Sprite* sprite : tileSprites)
		delete sprite;
}

void Tilemap::PlaceTiles() //reads the whole text file and places tiles as it goes along
{						   //a bit messy but it works
	std::ifstream inFile;
	inFile.open("../Assets/tilemap.txt");
	if (!inFile)
	{
		std::cout << "can't open file" << std::endl;
		return;
	}
	int currentLine = 0;
	std::string line;

	int screenX = 0;
	int screenY = 0;
	int y = 0;
	while (std::getline(inFile, line))
	{
		if (line.empty())
		{
			return; //as soon as there's an empty line it'll stop spawning stuff
		}
		if (currentLine % 13 == 0) //every screen is 11 tiles tall, and 2 lines are for the screen x and y
		{
			screenX = std::stoi(line);
		}
		else if (currentLine % 13 == 1)
		{
			screenY = std::stoi(line);
			y = 0;
		}
		else	
		{	
			for (int x = 0; x < screenW; x++) //spawns one row of tiles
			{
				char tileNum = 0;
				try
				{
					tileNum = line[2 * (__int64)x]; //annoying
					tileNum -= '0'; //the char '0' doesn't have the value 0, so we just offset it
				}
				catch (std::out_of_range& oor)
				{
					std::cout << "fucked up at: " << x << std::endl;
					tileNum = 0;
				}
				PlaceTile(x, y, screenX, screenY, (int)tileNum);
				//if (screenX < 0) std::cout << x << ' ' << y << '\n' << "screen: " << screenX << ' ' << screenY << std::endl;
			}
			y++;
		}
		currentLine++;
	}
	inFile.close();
}

void Tilemap::PlaceTile(int x, int y, int screenX, int screenY, int index)
{
	Vector2 pos = CoordsToVector2(x + screenX * screenW, y + screenY * screenH);
	Tile* tile;

	if (dynamic_cast<WallTile*>(palette[index]) != nullptr) //https://stackoverflow.com/questions/11951121/checking-if-a-pointer-points-to-a-particular-class-c
	{
		tile = new WallTile(palette[index]->GetSprite(), pos);
		WallTile* wall = new WallTile(palette[index]->GetSprite(), pos);
		wallTiles.push_back(wall);
	}
	else
	{
		tile = new Tile(palette[index]->GetSprite(), pos);
	}
	allTiles.push_back(tile);
}

void Tilemap::CreatePalette()
{
	SpriteCutter::GetResourceManager()->LoadImageFromFile(tileSet, "../Assets/tileset.png");
	 tileSprites = SpriteCutter::GetSprites(10, tileSet);
	for (int i = 0; i < tileSprites.size(); i++)
	{
		if (i < 2)
		{
			Tile* t = new Tile(tileSprites[i], Vector2());
			palette.push_back(t);
		}
		else
		{
			WallTile* wall = new WallTile(tileSprites[i], Vector2());
			palette.push_back(wall);
		}
	}
}

void Tilemap::Render(RenderManager& renderer, bool debug)
{
	for (int i = 0; i < allTiles.size(); i++)
	{
		allTiles[i]->Render(renderer, debug);
	}
}

Tile::Tile(Sprite* spr, Vector2 pos) : sprite(spr), transform(Transform())
{
	transform.position = pos;
	transform.SetUniformScale(SCALE);
	renderTransform.SetUniformScale(SCALE);
	renderTransform.position = pos + Camera::GetCamPosition();
}

void Tile::Render(RenderManager& renderer, bool debug)
{
	renderTransform.position = transform.position - Camera::GetCamPosition();
	renderer.Render(*sprite, renderTransform);
}

void WallTile::Render(RenderManager& renderer, bool debug)
{
	debugRect.x = collider.rect.x - (int)Camera::GetCamPosition().x;
	debugRect.y = collider.rect.y - (int)Camera::GetCamPosition().y;
	Tile::Render(renderer, debug);
	if (debug)
		renderer.Render(debugRect, debugColor);
}

WallTile::WallTile(Sprite* sprite, Vector2 pos) : Tile(Tile(sprite, pos))
{
	collider.SetSize(16.0f * SCALE, 10.0f * SCALE);
	collider.SetPosition((int)pos.x, (int)pos.y);
	debugRect = collider.rect;
}
