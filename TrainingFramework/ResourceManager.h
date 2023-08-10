#pragma once
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "../Utilities/utilities.h"
#include "Math.h"
#include <cstdio>

class ResourceManager {
private:
	Model** models;
	Texture** textures;
	Shaders** shaders;
	int* shaderInit;
	int numModels;
	int numTextures;
	int numShaders;

public:
	ResourceManager();
	int GetShaderInitById(int Id);
	Model* GetModelById(int Id);
	Texture* GetTextureById(int Id);
	Shaders* GetShaderById(int Id);
	~ResourceManager();
};