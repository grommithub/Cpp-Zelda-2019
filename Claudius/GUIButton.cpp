#include "GUIButton.h"
#include "ScreenDimentions.h"
#include <iostream>

Transform& GUIButton::GetTransform()
{
	return trans;
}

GUIButton::GUIButton(Vector2 position) : noHoverSprite(nullptr), debugCol(Color::Blue())
{
	trans.SetUniformScale(SCALE);
	image = new Image();
	SpriteCutter::GetResourceManager()->LoadImageFromFile(*image, "../Assets/selected.png");
	
	hoverSprite = Sprite();
	hoverSprite.SetImage(*image);
	hoverSprite.SetSource(0, 0, image->width, image->height);

	trans.position = position;

	width = hoverSprite.source.w * SCALE;
	height = hoverSprite.source.h * SCALE;

	debugRect.w = width;
	debugRect.h = height;
}

GUIButton::~GUIButton()
{
	//delete hoverSprite;
	//delete noHoverSprite;
}

bool GUIButton::Hovering(Vector2 mouse)
{
	if (mouse.x > trans.position.x&& mouse.x < trans.position.x + (float)width && mouse.y > trans.position.y&& mouse.y < trans.position.y + height)
	{
		OnHover();
		return true;
	}
	NotHovering();
	return false;
}

void GUIButton::OnHover()
{
	hovering = true;
	//activeSprite = hoverSprite;
}

void GUIButton::NotHovering()
{
	hovering = false;
	//activeSprite = noHoverSprite;
}

bool GUIButton::OnClick()
{
	if (!hovering) return false;
	return true;
}

void GUIButton::Render(RenderManager& renderer, bool debug)
{
	if (hovering) renderer.Render(hoverSprite, trans);
	else if(noHoverSprite != nullptr)renderer.Render(*noHoverSprite, trans);

	if (!debug) return;

	debugRect.x = (int)trans.position.x;
	debugRect.y = (int)trans.position.y;

	renderer.Render(debugRect, debugCol);
}
