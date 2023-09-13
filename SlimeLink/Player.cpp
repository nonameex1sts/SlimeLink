#include "stdafx.h"
#include "Math.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "Camera.h"
#include "Player.h"
#include "AudioManager.h"

Player::Player(Model* model, Texture* texture, Camera* camera, Shaders* shader, Vector3 position, Vector3 rotation, Vector3 scale, 
	GLint numFrames, GLint numActions, GLint currentAction, GLfloat frametime, bool isActive)
	: Animation(model, texture, camera, shader, position, rotation, scale + Vector3(-4.0f, -4.0f, 0.0f), numFrames, numActions, currentAction, frametime)
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

void Player::SetDrawnStatus(bool status)
{
	this->isDrawn = status;
}

bool Player::GetDrawnStatus()
{
	return isDrawn;
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

void Player::Key(unsigned char keyPressed, bool* hasMoved)
{
	//AWSD and arrowkeys for movement
	if (isActive) {
		//Check if player is active, the key is pressed and the player corresponding movement ability
		//If true, active the player moving ability, calculate next position and the direction to move (deltaPosition)
		if ((keyPressed & (1 << 0)) && canMoveLeft)
		{
			deltaPosition = Vector3(-SQUARE_SIZE, 0.0f, 0.0f);
			isMoving = true;
			nextPosition = position + deltaPosition;
			*hasMoved = true;
			AudioManager::GetInstance()->GetAudioById(3)->PlayMusic();
		}
		if ((keyPressed & (1 << 1)) && canMoveUp)
		{
			deltaPosition = Vector3(0.0f, -SQUARE_SIZE, 0.0f);
			isMoving = true;
			nextPosition = position + deltaPosition;
			*hasMoved = true;
			AudioManager::GetInstance()->GetAudioById(3)->PlayMusic();
		}
		if ((keyPressed & (1 << 2)) && canMoveRight)
		{
			deltaPosition = Vector3(SQUARE_SIZE, 0.0f, 0.0f);
			isMoving = true;
			nextPosition = position + deltaPosition;
			*hasMoved = true;
			AudioManager::GetInstance()->GetAudioById(3)->PlayMusic();
		}
		if ((keyPressed & (1 << 3)) && canMoveDown)
		{
			deltaPosition = Vector3(0.0f, SQUARE_SIZE, 0.0f);
			isMoving = true;
			nextPosition = position + deltaPosition;
			*hasMoved = true;
			AudioManager::GetInstance()->GetAudioById(3)->PlayMusic();
		}
	}
}

void Player::Move(float deltaTime)
{
	if (isMoving) 
	{
		//If player's position is close to its target, the player jump to the target and disable is moving ability
		if ((position - nextPosition).Length() < MOVEMENT_SNAP_DISTANCE)
		{
			position = nextPosition;
			isMoving = false;
		}
		//If not, the player jump a small step towards the target direction in each frame
		else 
		{
			position += deltaPosition * FRAME_TIME / (DELAY_KEY_TIME);
		}
		InitWorldMatrix();
	}
}