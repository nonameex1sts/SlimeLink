#include "stdafx.h"
#include "Math.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "Camera.h"
#include "Player.h"

Player::Player(Model* model, Texture* texture, Camera* camera, Shaders* shader, Vector3 position, Vector3 rotation, Vector3 scale, bool isActive) 
	: Object(model, texture, camera, shader, position, rotation, scale - Vector3(10.0f, 10.0f, 0.0f))
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
			Move(Vector3(-SQUARE_SIZE, 0.0f, 0.0f));
		}
		if ((keyPressed & (1 << 1)) && canMoveUp)
		{
			Move(Vector3(0.0f, -SQUARE_SIZE, 0.0f));
		}
		if ((keyPressed & (1 << 2)) && canMoveRight)
		{
			Move(Vector3(SQUARE_SIZE, 0.0f, 0.0f));
		}
		if ((keyPressed & (1 << 3)) && canMoveDown)
		{
			Move(Vector3(0.0f, SQUARE_SIZE, 0.0f));
		}
	}
}

void Player::Move(Vector3 deltaPosition)
{
	position += deltaPosition;
	InitWorldMatrix();
}