#pragma once

#include "Image.h"
#include "Sprite.h"
#include "Inventory.h"
#include "RenderManager.h"
#include "ScreenDimentions.h"
#include "SpriteCutter.h"
#include "Transform.h"
#include "Player.h"

#include "GUIButton.h"

#include "Text.h"
#include "Font.h"

#define HEARTS_START_X 175
#define HEARTS_START_Y 36

#define A_ITEM_START_X 151
#define A_ITEM_START_Y 20

#define B_ITEM_START_X 127
#define B_ITEM_START_Y 20

#define RUPEES_START_X 95
#define RUPEES_START_Y 10

#define KEYS_START_X   95 
#define KEYS_START_Y   26

#define BOMBS_START_X  95
#define BOMBS_START_Y  34

#define ITEMS_START_X 125
#define ITEMS_START_Y 45

#define MUTE_X		 123
#define MUTE_Y		 24

class UI
{
	std::vector<GUIButton*> buttons;

	GUIButton muteButton;

	Vector2 mousePosition;

	Inventory& inventory;

	Font font;
	Color textColour;

	Text rupeesCounter;
	Text keysCounter;
	Text bombsCounter;

	Sprite bg;
	Sprite sword;
	Image backdrop;

	Transform bgTrans;

	Player* player;

	int& totalhealth;
	int& currenthealth;
	Sprite* swordSprite;

	Image iconSheet;

	std::vector<Transform> heartTransforms;
	Transform swordTransform;
	
	Sprite wholeHeart;
	Sprite halfHeart;
	Sprite emptyHeart;


	Image muteIMG;

	Sprite* muted;
	Sprite* unMuted;

	std::vector<Sprite*> sprites;

	float yOffset;
public:
	bool isMuted;
	UI(Player* p, Inventory* inv);
	~UI();
	void Render(RenderManager& renderer, bool debug);
	void Update(float dt);
	void TogglePaused();
	void OnMouseMove(Vector2 position);
	void OnClick();
	void OnRelease();
	bool menu;
};

