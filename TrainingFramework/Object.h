#pragma once
#include "Math.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "Camera.h"
#include "../Utilities/utilities.h"

class Object {
private:
	Model* model;
	Texture* texture;
	Camera* camera;
	Shaders* shader;
	Matrix world;

public:
	Object(Model* model, Texture* texture, Camera* camera, Shaders* shader, Vector3 position, Vector3 rotation, Vector3 scale);
	Object(char* modelLink, char* textureLink, Camera* camera, Vector3 position, Vector3 rotation, Vector3 scale);
	void InitWorldMatrix(Vector3 position, Vector3 rotation, Vector3 scale);
	void Update();
	void Draw();
	void Key();
	void Move();
	void Rotate();
	Matrix CalculateWVP();
	~Object();
};