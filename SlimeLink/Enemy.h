#pragma once

#include "Player.h"

class Enemy : public Player {
private:
	Vector3 playerLockPosition;

public:
	Enemy(Model* model, Texture* texture, Camera* camera, Shaders* shader, Vector3 position, Vector3 rotation, Vector3 scale,
		GLint numFrames, GLint numActions, GLint currentAction, GLfloat frametime, bool isActive, Vector3 playerLockPosition);
	~Enemy();
	void SetPlayerLockPosition(Vector3 playerLockPosition);
	void Key(unsigned char keyPressed);
};