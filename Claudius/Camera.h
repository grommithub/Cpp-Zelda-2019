#pragma once
#include "ScreenDimentions.h"
#include "Transform.h"
#include "Player.h"

class Camera
{
public:
	static Vector2 GetCamPosition() { return cameraPosition;  }

	Camera(Player* player);

	~Camera();
	bool GetMoving() { return moving; }
	void CheckForTransition();
	void Update(float dt);

private:
	float freezeTime;
	Vector2 distance;
	Vector2 lastScreenPosition;
	static Vector2 cameraPosition;
	Vector2 desiredPosition;
	float moveTime;
	float currentMoveTime;
	bool moving;

	Player* player;

	Vector2 playerLastPosition;
	Vector2 playerDesiredPosition; //after screen scroll

	struct screenCoords
	{
		int x, y;
	};
	enum directions 
	{
		LEFT,
		RIGHT,
		DOWN,
		UP
	};
	void SetNewCameraDestination(int direction);
	void SmoothTransition(float dt);
};

