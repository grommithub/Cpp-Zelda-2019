#pragma once

#include "SpriteCutter.h"
#include "Vector2.h"
#include "Transform.h"
#include "RenderManager.h"
#include "Color.h"

class GUIButton
{
	bool hovering;
	Transform trans;
	int width;
	int height;
	Rectangle debugRect;
	Color debugCol;


	Image* image;
	Sprite* noHoverSprite;
	Sprite hoverSprite;


public:
	Transform& GetTransform();

	GUIButton(Vector2 position);
	~GUIButton();
	void Render(RenderManager& renderer, bool debug);

	bool Hovering(Vector2 mouse);
	virtual void OnHover();
	void NotHovering();
	virtual bool OnClick();

};

