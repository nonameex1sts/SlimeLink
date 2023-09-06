#pragma once
#include "../Utilities/utilities.h"
#include "Math.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "Camera.h"
#include "Object.h"

class Picture : public Object {
private:
	bool isActive;
	Vector3 startPos = position;

public:
	Picture();
	Picture(Model* model, Texture* texture, Camera* camera, Shaders* shader, Vector3 position, Vector3 rotation, Vector3 scale, int isActive);
	void Update(Vector3 newPosition, float time);
	void Key();
	void MouseClick(int x, int y);
	void MouseMove();
	void Move();
	void Rotate();
	bool getActive();
	void setActive(bool status);
	~Picture();
};