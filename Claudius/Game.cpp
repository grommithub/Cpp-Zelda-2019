//Daniel Burt, 1/19/2020


#include "Game.h"
#include <assert.h>
#include "ResourceManager.h"
#include "RenderManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "SpriteCutter.h"
#include "Camera.h"
#include "ScreenDimentions.h"
#include "Item.h"

#include "HeartPickup.h"

#include <string>


Game::Game(ResourceManager& resourceManager, SoundManager& soundManager) : debugView(false), resourceManager(resourceManager), soundManager(soundManager), updateRate(0.0f), currentTimer(0.0f), camera(nullptr), ui(nullptr), player(nullptr), tilemap(nullptr), debugCol(Color::Green())
{
	Initialize();
	resourceManager.LoadFontFromFile(font, "../Assets/NES.ttf", 16);
	font.size = 16;
	debugText.color = debugCol;
	debugText.transform.position = Vector2(10.0f, 10.0f);
	debugText.transform.SetUniformScale(1.0f);
}

Game::~Game()
{
	delete player;
	delete camera;
	delete tilemap;
	delete inv;
	delete ui;

	for (Enemy* e : enemies) delete e;
	enemies.clear();
	for (Particle* p : particles) delete p;
	particles.clear();
	for (Pickup* p : pickups) delete p;
	pickups.clear();
}

bool Game::Enter(int& width, int& height, std::string& title)
{
	width = WIDTH * SCALE;
	height = HEIGHT * SCALE;
	title = "The Legend of Zelda";
	
	return true;
}

void Game::Initialize()
{
	SpriteCutter::SetResourceManager(resourceManager);
	Entity::SetResourceManager(resourceManager);
	Entity::SetParticleVector(particles);
	Enemy::SetPickupVector(&pickups);
	Entity::SetSoundPlayer(&soundManager);
	delete player;
	delete camera;
	delete tilemap;
	delete inv;
	delete ui;

	resourceManager.LoadSoundFromFile(enemyHitSound, "../Assets/Audio/LOZ_Enemy_Hit.ogg");
	resourceManager.LoadSoundFromFile(enemyDeathSound, "../Assets/Audio/LOZ_Enemy_Die.ogg");
	resourceManager.LoadSoundFromFile(itemPickUpSound, "../Assets/Audio/LOZ_Get_Heart.ogg");
	resourceManager.LoadMusicFromFile(zeldaTheme, "../Assets/Audio/Overworld.ogg");

	for (Enemy* e : enemies) delete e;
	enemies.clear();
	for (Particle* p : particles) delete p;
	particles.clear();
	for (Pickup* p : pickups) delete p;
	pickups.clear();

	player = new Player();
	camera = new Camera(player);
	tilemap = new Tilemap();
	inv = new Inventory();
	ui = new UI(player, inv);

	soundManager.PlayMusic(zeldaTheme, -1);

	for (int i = 0; i < 3; i++)
	{
		enemies.push_back(new Octorok(tilemap->CoordsToVector2(3, 3 + i, -1, 0)));
	}
	for (int i = 0; i < 3; i++)
	{
		enemies.push_back(new Octorok(tilemap->CoordsToVector2(3 + 2 * i, 3 + i, 1, 0)));
	}


	Pickup::SetPlayer(player);
}


bool Game::Update(float dt)
{	
	if (ui->isMuted) soundManager.SetMusicVolume(zeldaTheme, 0);
	else soundManager.SetMusicVolume(zeldaTheme, 100);

	if (player->GetHealth() <= 0)
	{
		std::cout << "You died!" << std::endl;
		Initialize();
		return true;
	}

	if (enemies.size() <= 0)
	{
		std::cout << "You WIN!" << std::endl;
		Initialize();
		return true;
	}

	debugText.text = std::to_string(1.0f / dt);
	if (dt > 0.1f) dt = 0.1f;
	currentTimer += dt;
	if (currentTimer >= updateRate && !camera->GetMoving() && !inv->menu)
	{
		player->Update(dt);
		tilemap->CollisionCheck(player);
		for (int i = 0; i < pickups.size(); i++)
		{
			if (CollisionManager::CheckCollision(pickups[i]->GetCollider(), player->GetCollider()))
			{
				inv->ObtainItem(pickups[i]->GivePlayerPickup()); 
				//method returns item to add to inv, if it's null it'll do nothing
				//if item just gives resources (rupees, bombs, etc) it does so within the method
				delete pickups[i];
				pickups.erase(pickups.begin() + i);
				soundManager.PlaySound(itemPickUpSound, 0);
			}
		}
		for (int i = 0; i < enemies.size(); i++)
		{
			if (player->GetStabbing())
			{
				if (CollisionManager::CheckCollision(player->GetSword()->GetCollider(), enemies[i]->GetCollider()))
				{
					if(enemies[i]->TakeDamage(player->GetSword()->GetDamage(), player->GetMiddle()))
						soundManager.PlaySound(enemyHitSound, 0);
				}
				if (enemies[i]->GetHealth() <= 0)
				{
					enemies[i]->Die();
					delete enemies[i];
					if (i == enemies.size() - 1) enemies.pop_back();
					else
					{
						enemies.erase(enemies.begin() + i);
					}
					soundManager.PlaySound(enemyDeathSound, 0);
					break;
				}
			}
			enemies[i]->Update(dt);
			tilemap->CollisionCheck(enemies[i]);

			if (CollisionManager::CheckCollision(player->GetCollider(), enemies[i]->GetCollider()) && !enemies[i]->Offscreen())
			{
				player->TakeDamage(enemies[i]->GetDamage(), enemies[i]->GetMiddle());
			}
		}
		currentTimer -= updateRate;
		for (int i = 0; i < particles.size(); i++)
		{
			particles[i]->Animate(dt);
			if (particles[i]->GetDone())
			{
				delete particles[i];
				if (i == particles.size() - 1) particles.pop_back();
				else
					particles.erase(particles.begin() + i);
			}
		}
		ui->Update(dt);
	}
	camera->Update(dt);	
	return true;
}

void Game::Render(RenderManager& renderManager)
{
	bool debug = false;
	tilemap->Render(renderManager, debugView);
	player->Render(renderManager, debugView);

	for (Enemy* ent : enemies)
	{
		ent->Render(renderManager, debugView);
	}
	for (Pickup* p : pickups)
	{
		p->Render(renderManager, debugView);
	}
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i]->Render(renderManager);
	}
	if(debugView) 
		renderManager.Render(font, debugText);
	ui->Render(renderManager, debugView);
}

void Game::OnKeyDown(KeyCode key)
{
	if (!camera->GetMoving())player->OnKeyDown(key);
	if (key == KeyCode::R) Initialize();
	if (key == KeyCode::D) debugView = !debugView;


	if (!debugView) return;
	if (key == KeyCode::O) player->GetHealthRef()--;
	if (key == KeyCode::P) player->GetHealthRef()++;
}

void Game::OnMouseMove(int x, int y)
{
	ui->OnMouseMove(Vector2((float)x, (float)y));
}

void Game::OnMouseKeyUp()
{
	ui->OnClick();
}

void Game::OnMouseKeyDown()
{
	ui->OnRelease();
}

void Game::OnKeyUp(KeyCode key)
{
	player->OnKeyUp(key);
	if (key == KeyCode::ESCAPE)
	{
		ui->TogglePaused();
	}
}
