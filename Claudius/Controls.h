#pragma once
#include "KeyCode.h"

class Controls
{
public:
	KeyCode leftKey;
	KeyCode rightKey;
	KeyCode downKey;
	KeyCode upKey;

	KeyCode swordKey;
	KeyCode itemKey;

	KeyCode pauseKey;

	static Controls PlayerOne();
};
