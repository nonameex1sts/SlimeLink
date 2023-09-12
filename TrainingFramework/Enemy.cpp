#include "stdafx.h"
#include "Enemy.h"
#include <math.h>

Enemy::Enemy(Model* model, Texture* texture, Camera* camera, Shaders* shader, Vector3 position, Vector3 rotation, Vector3 scale, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frametime, bool isActive, Vector3 pPlayerPositionLock)
	: Player(model, texture, camera, shader, position, rotation, scale, numFrames, numActions, currentAction, frametime, isActive)
{
	this->playerLockPosition = playerLockPosition;
}

Enemy::~Enemy()
{
}

void Enemy::SetPlayerLockPosition(Vector3 playerLockPosition)
{
	this->playerLockPosition = playerLockPosition;
}

void Enemy::Key()
{
	Vector3 direction = playerLockPosition - this->position;
	bool* hasMoved = new bool;
	*hasMoved = false;

	if (fabs(direction.x) > fabs(direction.y))
	{
		if (direction.x < 0)
		{
			Player::Key(1 << 0, hasMoved);
		}
		else if (direction.x > 0)
		{
			Player::Key(1 << 2, hasMoved);
		}

		if (!(*hasMoved))
		{
			if (direction.y < 0)
			{
				Player::Key(1 << 1, hasMoved);
			}
			else if (direction.y > 0)
			{
				Player::Key(1 << 3, hasMoved);
			}
		}
	}
	else
	{
		if (direction.y < 0)
		{
			Player::Key(1 << 1, hasMoved);
		}
		else if (direction.y > 0)
		{
			Player::Key(1 << 3, hasMoved);
		}

		if (!(*hasMoved))
		{
			if (direction.x < 0)
			{
				Player::Key(1 << 0, hasMoved);
			}
			else if (direction.x > 0)
			{
				Player::Key(1 << 2, hasMoved);
			}
		}
	}

	delete hasMoved;
}