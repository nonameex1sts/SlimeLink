#include "stdafx.h"
#include "Math.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "Camera.h"
#include "Player.h"

Player::Player(Model* model, Texture* texture, Camera* camera, Shaders* shader, Vector3 position, Vector3 rotation, Vector3 scale, bool isActive) 
	: Object(model, texture, camera, shader, position, rotation, scale)
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

void Player::Key(unsigned char keyPressed)
{
	if (keyPressed & (1 << 4))
	{
		Move(Vector3(-SQUARE_SIZE, 0.0f, 0.0f));
	}
	if (keyPressed & (1 << 5))
	{
		Move(Vector3(0.0f, -SQUARE_SIZE, 0.0f));
	}
	if (keyPressed & (1 << 6))
	{
		Move(Vector3(SQUARE_SIZE, 0.0f, 0.0f));
	}
	if (keyPressed & (1 << 7))
	{
		Move(Vector3(0.0f, SQUARE_SIZE, 0.0f));
	}
}

void Player::Move(Vector3 deltaPosition)
{
	Object::Move(deltaPosition);
}