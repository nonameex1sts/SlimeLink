#pragma once
#include "Object.h"
#include "../Utilities/utilities.h"

class Player : public Object {
private:
	bool isActive;

public:
	Player();
	Player(Model* model, Texture* texture, Camera* camera, Shaders* shader, Vector3 position, Vector3 rotation, Vector3 scale, bool isActive);
	~Player();
	void Key(unsigned char keyPressed, bool canMoveLeft, bool canMoveRight, bool canMoveUp, bool canMoveDown);
	void Move(Vector3 deltaPosition);
	void SetActiveStatus(bool status);
	bool GetActiveStatus();
};