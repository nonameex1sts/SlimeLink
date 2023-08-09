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
	int shaderInit;
	Matrix world;

public:
	Object(char* modelLink, char* textureLink, Camera* camera);
	int GetShaderInit();
	void Update();
	void Draw();
	void Key();
	void Move();
	void Rotate();
	Matrix CalculateWVP();
	void Cleanup();
	~Object();
};