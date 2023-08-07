#pragma once
#include "Math.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "Camera.h"
#include "Globals.h"
#include "../Utilities/utilities.h"

class Object {
public:
	Model* model;
	Texture* texture;
	Camera* camera;
	Shaders shader;
	int shaderInit;
	Matrix world;

	Object();
	Object(char* modelLink, char* textureLink);
	void Draw();
	void Cleanup();
	~Object();
};