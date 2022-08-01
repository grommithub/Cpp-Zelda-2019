#include "Camera.h"
#include <iostream>

Vector2 Camera::cameraPosition{ 0,0 };

Camera::Camera(Player* player) : player(player), moving(false), currentMoveTime(0), moveTime(2.5f), freezeTime(1.0f)
{
	cameraPosition = Vector2(0, 0);
}

Camera::~Camera()
{
}

void Camera::SetNewCameraDestination(int direction)
{
	
	Vector2 cameraMoveDirection;
	playerLastPosition = player->GetTransform().position;
	switch (direction)
	{
	case LEFT:
		cameraMoveDirection += Vector2::Left() * WIDTH;
		playerDesiredPosition = playerLastPosition + Vector2::Left() * 16.0f * SCALE;
		break;

	case RIGHT:
		cameraMoveDirection += Vector2::Right() * WIDTH;
		playerDesiredPosition = playerLastPosition + Vector2::Right() * 16.0f * SCALE;
		break;
	case UP:
		cameraMoveDirection += Vector2::Up() * VIEWPORT_HEIGHT;
		playerDesiredPosition = playerLastPosition + Vector2::Up() * 16.0f * SCALE;
		break;

	case DOWN:
		cameraMoveDirection += Vector2::Down() * VIEWPORT_HEIGHT;
		playerDesiredPosition = playerLastPosition + Vector2::Down() * 16.0f * SCALE;
		break;

	default:
		return;
		break;
	}
	desiredPosition = cameraPosition + cameraMoveDirection * SCALE;
	currentMoveTime = moveTime + freezeTime;
	distance = desiredPosition - cameraPosition;
	lastScreenPosition = cameraPosition;
	moving = true;
}

void Camera::SmoothTransition(float dt)
{
	currentMoveTime -= dt;

	if (currentMoveTime <= moveTime)
	{
		distance = (desiredPosition - lastScreenPosition) * (currentMoveTime / moveTime);
		cameraPosition = desiredPosition - distance;
		distance = distance * (currentMoveTime / moveTime);
		cameraPosition = desiredPosition - distance;

		Vector2 playerDistance = (playerDesiredPosition - playerLastPosition) * (currentMoveTime / moveTime);
		player->GetTransform().position = playerDesiredPosition - playerDistance;

	}
	if (currentMoveTime <= 0.0f)
	{
		cameraPosition = desiredPosition;
		moving = false;
	}
}

void Camera::CheckForTransition()
{
	if (player->GetTransform().position.x < cameraPosition.x)
	{
		SetNewCameraDestination(LEFT);
	}
	else if (player->GetTransform().position.x + player->GetCollider().rect.w > cameraPosition.x + (float)WIDTH * (float)SCALE)
	{
		SetNewCameraDestination(RIGHT);
	}
	else if (player->GetTransform().position.y < cameraPosition.y + UI_HEIGHT * SCALE)
	{
		SetNewCameraDestination(UP);
	}
	else if (player->GetTransform().position.y + player->GetCollider().rect.w > cameraPosition.y + (float)HEIGHT * (float)SCALE)
	{
		SetNewCameraDestination(DOWN);
	}
}
void Camera::Update(float dt)
{
	if(!moving) CheckForTransition();
	if (moving)
	{
		SmoothTransition(dt);
	}

}
