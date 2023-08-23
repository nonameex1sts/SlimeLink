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

public:
	Player();
	Player(Model* model, Texture* texture, Camera* camera, Shaders* shader, Vector3 position, Vector3 rotation, Vector3 scale, bool isActive);
	~Player();
	void Key(unsigned char keyPressed);
	void Move(Vector3 deltaPosition);
	void SetActiveStatus(bool status);
	bool GetActiveStatus();
	void SetMoveLeftStatus(bool status);
	void SetMoveRightStatus(bool status);
	void SetMoveUpStatus(bool status);
	void SetMoveDownStatus(bool status);
};