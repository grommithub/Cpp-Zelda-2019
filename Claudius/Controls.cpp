#include "Controls.h"


Controls Controls::PlayerOne()
{
	Controls controls = Controls();
	controls.upKey		= KeyCode::UP_ARROW;
	controls.downKey	= KeyCode::DOWN_ARROW;
	controls.leftKey	= KeyCode::LEFT_ARROW;
	controls.rightKey   = KeyCode::RIGHT_ARROW;

	controls.swordKey	= KeyCode::Z;
	controls.itemKey    = KeyCode::X;

	return controls;
}
