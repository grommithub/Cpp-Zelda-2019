#include "UI.h"
#include <iostream>


UI::UI(Player* p, Inventory* inv) : player(p), currenthealth(player->GetHealthRef()), totalhealth(player->GetTotalHealth()), inventory(*inv), menu(false), muteButton(GUIButton(Vector2()))
{
	muteButton = GUIButton(Vector2(MUTE_X, MUTE_Y - VIEWPORT_HEIGHT) * SCALE);

	SpriteCutter::GetResourceManager()->LoadImageFromFile(muteIMG, "../Assets/mute.png");

	std::vector<Sprite*> mutes = SpriteCutter::GetSprites(2, muteIMG);
	unMuted = mutes[0];
	muted = mutes[1];

	SpriteCutter::GetResourceManager()->LoadImageFromFile(backdrop, "../Assets/test-ui.png");
	bg.SetImage(backdrop);
	bg.SetSource(0,0,backdrop.width, backdrop.height);
	bgTrans.SetUniformScale(SCALE);
	bgTrans.SetPosition(0.0f, (float)-VIEWPORT_HEIGHT * SCALE);

	if (player->GetSword() != nullptr)
		swordSprite = player->GetSword()->GetSwordSprite();

	swordTransform.position = Vector2(A_ITEM_START_X, A_ITEM_START_Y);
	swordTransform.position = swordTransform.position * SCALE;
	swordTransform.SetUniformScale(SCALE);

	SpriteCutter::GetResourceManager()->LoadImageFromFile(iconSheet, "../Assets/items-sheet.png");
	sprites = SpriteCutter::GetSprites(10, iconSheet);
	wholeHeart = *sprites[7];
	halfHeart = *sprites[8];
	emptyHeart = *sprites[9];

	SpriteCutter::GetResourceManager()->LoadFontFromFile(font, "../Assets/NES.ttf", 10 * SCALE);
	font.size = 16;
	
	textColour = Color::White();

	rupeesCounter.transform.position = Vector2(RUPEES_START_X, RUPEES_START_Y) * SCALE; 
	keysCounter.transform.position = Vector2(KEYS_START_X, KEYS_START_Y) * SCALE;
	bombsCounter.transform.position = Vector2(BOMBS_START_X, BOMBS_START_Y) * SCALE;

	rupeesCounter.color = textColour;
	bombsCounter.color = textColour;
	keysCounter.color = textColour;

	for (int i = 0; i < 16; i++)
	{
		Transform t = Transform();
		t.SetPosition(static_cast<float>(HEARTS_START_X + (8 * ((i % 8)))), static_cast<float>(HEARTS_START_Y - ((i / 8) * (8)))); //
		t.position = t.position * SCALE;
		t.SetUniformScale(SCALE);
		heartTransforms.push_back(t);
	}

}
UI::~UI()
{
	for (Sprite* sprite : sprites)
	{
		delete sprite;
	}
	delete muted;
	delete unMuted;
}

void UI::Render(RenderManager& renderer, bool debug)
{
	renderer.Render(bg, bgTrans);
	for (int i = 1; i <= totalhealth / 2; i++) //i starts at one so that 2 * i =/= 0
	{
		Sprite* heart;
		if (currenthealth >= 2 * i)
			heart = &wholeHeart;
		else if (currenthealth == (2 * i) - 1)
			heart = &halfHeart;
		else heart = &emptyHeart;
		renderer.Render(*heart, heartTransforms[i]);
	}
	if (player->GetSword() != nullptr)
	{
		sword = *player->GetSword()->GetSwordSprite();
		sword.SetFlip(Sprite::Flip::None);
		renderer.Render(sword, swordTransform);
	}

	
	rupeesCounter.text = "X" + std::to_string(inventory.rupees);
	bombsCounter.text = "X" + std::to_string(inventory.bombs);
	keysCounter.text = "X" + std::to_string(inventory.keys);

	renderer.Render(font, rupeesCounter);
	renderer.Render(font, keysCounter);
	renderer.Render(font, bombsCounter);

	muteButton.Render(renderer, debug);
	//for (GUIButton* btn : buttons)
	//	btn->Render(renderer, debug);

	if (isMuted)
	{
		renderer.Render(*muted, muteButton.GetTransform());
	}
	else
	{
		renderer.Render(*unMuted, muteButton.GetTransform());
	}
	
}

void UI::Update(float dt)
{

}

void UI::TogglePaused()
{
	menu = !menu;
	int sign;

	if (menu)
		sign = 1;
	else
		sign = -1;

	//moving stuff up and down
	for (int i = 0; i < heartTransforms.size(); i++)
	{
		heartTransforms[i].position.y += VIEWPORT_HEIGHT * SCALE * sign;
	}
	rupeesCounter.transform.position.y += VIEWPORT_HEIGHT * SCALE * sign;
	keysCounter.transform.position.y += VIEWPORT_HEIGHT * SCALE * sign;
	bombsCounter.transform.position.y += VIEWPORT_HEIGHT * SCALE * sign;
	bgTrans.position.y += VIEWPORT_HEIGHT * SCALE * sign;
	swordTransform.position.y += VIEWPORT_HEIGHT * SCALE * sign;

	muteButton.GetTransform().position.y += VIEWPORT_HEIGHT * SCALE * sign;
}

void UI::OnMouseMove(Vector2 position)
{
	mousePosition = position;
	muteButton.Hovering(mousePosition);
}

void UI::OnClick()
{
	if (muteButton.OnClick())
	{
		isMuted = !isMuted;
	}
		
}

void UI::OnRelease()
{

}
