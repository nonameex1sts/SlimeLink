#pragma once

# define KEY_LEFT				'A'
# define KEY_RIGHT				'D'
# define KEY_UP					'W'
# define KEY_DOWN				'S'
# define KEY_MOVE_LEFT			VK_LEFT
# define KEY_MOVE_RIGHT			VK_RIGHT
# define KEY_MOVE_FORWARD		VK_UP
# define KEY_MOVE_BACKWARD		VK_DOWN

# define SQUARE_SIZE			40.0f

#define DELAY_KEY_TIME			0.1f
#define DELAY_STATE_PLAYER		0.03f

#define MOVEMENT_SNAP_DISTANCE	20.0f

class Globals
{
public:
	static const int screenWidth = 1280;
	static const int screenHeight = 720;
};