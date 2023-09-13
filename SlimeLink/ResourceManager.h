#pragma once
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "../Utilities/utilities.h"
#include "Math.h"
#include <cstdio>

class ResourceManager {
private:
	static ResourceManager* ms_pInstance;
	Model** pModels;
	Texture** pTextures;
	Shaders** pShaders;
	int* p_ishaderInit;
	int inumModels;
	int inumTextures;
	int inumShaders;
	ResourceManager();
	~ResourceManager();

public:
	static void CreateInstance()
	{
		if (ms_pInstance == nullptr)
			ms_pInstance = new ResourceManager();
	};

	static ResourceManager* GetInstance()
	{
		return ms_pInstance;
	};

	static void DestroyInstance()
	{
		if (ms_pInstance != nullptr)
		{
			delete ms_pInstance;
			ms_pInstance = nullptr;
		}
	};

	int GetShaderInitById(int Id);
	Model* GetModelById(int Id);
	Texture* GetTextureById(int Id);
	Shaders* GetShaderById(int Id);
};