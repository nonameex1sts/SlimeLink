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
	void Key(unsigned char keyPressed);
	void Move(Vector3 deltaPosition);
	bool GetActiveStatus();
};