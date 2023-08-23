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

public:
	Picture();
	Picture(Model* model, Texture* texture, Camera* camera, Shaders* shader, Vector3 position, Vector3 rotation, Vector3 scale, int isActive);
	void Update();
	void Key();
	void MouseClick(int x, int y);
	void MouseMove();
	void Move();
	void Rotate();
	bool getActive();
	~Picture();
};