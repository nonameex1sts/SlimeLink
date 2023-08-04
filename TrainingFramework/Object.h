#pragma once
#include "Math.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "../Utilities/utilities.h"

class Object {
public:
	Model* model;
	Texture* texture;
	Shaders shader;
	int shaderInit;

	Object();
	Object(char* modelLink, char* textureLink);
	void Draw();
	void Cleanup();
	~Object();
};