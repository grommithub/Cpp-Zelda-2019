#pragma once

#include <vector>
#include "KeyCode.h"

#include "Font.h"
#include "Text.h"
#include "Sound.h"
#include "Music.h"
#include "Image.h"

#include "Entity.h"
#include "Player.h"
#include "Camera.h"
#include "Tilemap.h"
#include "UI.h"


#include "Octorok.h"
#include "Particle.h"

struct RenderManager;
struct ResourceManager;
struct SoundManager;



class Game
{
	ResourceManager& resourceManager;
	SoundManager& soundManager;
public:
	void Initialize();

	bool debugView;
	Text debugText;
	Font font;
	Color debugCol;
	Inventory* inv;

	Sound enemyHitSound;
	Sound enemyDeathSound;
	Sound itemPickUpSound;
	Music zeldaTheme;

	std::vector<Pickup*> pickups;
	Tilemap* tilemap;
	UI* ui;
	Camera* camera;
	std::vector<Octorok*> enemies;
	Player* player;
	std::vector<Particle*> particles;
	float updateRate;
	float currentTimer;
	

	// references to a resource and sound manager sent in the constructor
	Game(ResourceManager& resourceManager, SoundManager& soundManager);
	~Game();

	// References sent to the game from the base to set the window size and name
	bool Enter(int& width, int& height, std::string& title);


	// If Games update returns false the program will exit, dt is milliseconds passed since last frame
	bool Update(float dt);

	// reference to the rendermanager sent in the function call, make sure to separate update logic from render logic
	void Render(RenderManager& rendererManager);
	void OnKeyDown(KeyCode key);
	void OnMouseMove(int x, int y);
	void OnMouseKeyUp();
	void OnMouseKeyDown();
	void OnKeyUp(KeyCode key);
};