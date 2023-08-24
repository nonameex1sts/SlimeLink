#include "stdafx.h"
#include "Math.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "Camera.h"
#include "Player.h"

Player::Player(Model* model, Texture* texture, Camera* camera, Shaders* shader, Vector3 position, Vector3 rotation, Vector3 scale, bool isActive) 
	: Object(model, texture, camera, shader, position, rotation, scale - Vector3(15.0f, 15.0f, 0.0f))
{
	this->isActive = isActive;
}

Player::~Player()
{
}

bool Player::GetActiveStatus()
{
	return isActive;
}

void Player::SetMoveLeftStatus(bool status)
{
	this->canMoveLeft = status;
}

void Player::SetMoveRightStatus(bool status)
{
	this->canMoveRight = status;
}

void Player::SetMoveUpStatus(bool status)
{
	this->canMoveUp = status;
}

void Player::SetMoveDownStatus(bool status)
{
	this->canMoveDown = status;
}

void Player::SetActiveStatus(bool status)
{
	this->isActive = status;
}

void Player::Key(unsigned char keyPressed)
{
	//AWSD for movement
	if (isActive) {
		if ((keyPressed & (1 << 0)) && canMoveLeft)
		{
			deltaPosition = Vector3(-SQUARE_SIZE, 0.0f, 0.0f);
			isMoving = true;
			nextPosition = position + deltaPosition;
		}
		if ((keyPressed & (1 << 1)) && canMoveUp)
		{
			deltaPosition = Vector3(0.0f, -SQUARE_SIZE, 0.0f);
			isMoving = true;
			nextPosition = position + deltaPosition;
		}
		if ((keyPressed & (1 << 2)) && canMoveRight)
		{
			deltaPosition = Vector3(SQUARE_SIZE, 0.0f, 0.0f);
			isMoving = true;
			nextPosition = position + deltaPosition;
		}
		if ((keyPressed & (1 << 3)) && canMoveDown)
		{
			deltaPosition = Vector3(0.0f, SQUARE_SIZE, 0.0f);
			isMoving = true;
			nextPosition = position + deltaPosition;
		}
	}
}

void Player::Move(float deltaTime)
{
	if (isMoving) 
	{
		if ((position - nextPosition).Length() < MOVEMENT_SNAP_DISTANCE)
		{
			position = nextPosition;
			isMoving = false;
		}
		else 
		{
			position += deltaPosition * deltaTime / (DELAY_KEY_TIME);
		}
		InitWorldMatrix();
	}
}