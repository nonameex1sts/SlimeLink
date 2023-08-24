#pragma once
#include "Object.h"
#include "../Utilities/utilities.h"

class Player : public Object {
private:
	bool isActive;
	bool canMoveLeft = true;
	bool canMoveRight = true;
	bool canMoveUp = true;
	bool canMoveDown = true;

	bool isMoving = false;
	Vector3 deltaPosition;
	Vector3 nextPosition;

public:
	Player();
	Player(Model* model, Texture* texture, Camera* camera, Shaders* shader, Vector3 position, Vector3 rotation, Vector3 scale, bool isActive);
	~Player();
	void Key(unsigned char keyPressed);
	void Move(float deltaTime);
	void SetActiveStatus(bool status);
	bool GetActiveStatus();
	void SetMoveLeftStatus(bool status);
	void SetMoveRightStatus(bool status);
	void SetMoveUpStatus(bool status);
	void SetMoveDownStatus(bool status);
};