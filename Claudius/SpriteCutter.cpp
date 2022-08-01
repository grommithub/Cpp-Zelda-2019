#include "SpriteCutter.h"

ResourceManager* SpriteCutter::resource{ nullptr };

std::vector<Sprite*> SpriteCutter::GetSprites(int count, Image& sheet)
{
	std::vector<Sprite*> sprites;
	for (int i = 0; i < count; i++)
	{
		Sprite* sp = new Sprite();
		sp->SetImage(sheet);
		sp->SetSource(i * (sheet.GetWidth() / count), 0, (sheet.GetWidth() / count), sheet.GetHeight());
		sprites.push_back(sp);
	}
	return sprites;
}

//these are all deleted where they are used
