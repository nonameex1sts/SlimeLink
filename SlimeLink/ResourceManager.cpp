#include "stdafx.h"
#include "ResourceManager.h"
#include <string>

ResourceManager* ResourceManager::ms_pInstance = nullptr;

ResourceManager::ResourceManager()
{
	FILE* filePointer = fopen("../SlimeLink/RM.txt", "r");
	int id;
	char* filePath = new char[100];

	//Load data form RM.txt and initialize models
	fscanf(filePointer, "#Models: %d\n", &inumModels);

	pModels = (Model**)malloc(sizeof(Model*) * inumModels);

	for (int i = 0; i < inumModels; i++)
	{
		fscanf(filePointer, "ID %d\n", &id);
		fscanf(filePointer, "FILE %s\n", filePath);
		pModels[i] = new Model(filePath);
	}

	//Load data form RM.txt and initialize textures
	fscanf(filePointer, "#2D Textures: %d\n", &inumTextures);
	pTextures = (Texture**)malloc(sizeof(Texture*) * inumTextures);

	for (int i = 0; i < inumTextures; i++)
	{
		fscanf(filePointer, "ID %d\n", &id);
		fscanf(filePointer, "FILE %s\n", filePath);

		pTextures[i] = (Texture*)malloc(sizeof(Texture));
		*(pTextures[i]) = Texture(filePath);
	}

	//Load data form RM.txt and initialize shaders
	char* fileVertexShader = new char[100];
	char* fileFragmentShader = new char[100];
	fscanf(filePointer, "#Shaders: %d\n", &inumShaders);

	pShaders = (Shaders**)malloc(sizeof(Shaders*) * inumShaders);
	p_ishaderInit = (int*)malloc(sizeof(int) * inumShaders);

	for (int i = 0; i < inumShaders; i++)
	{
		fscanf(filePointer, "ID %d\n", &id);
		fscanf(filePointer, "VS %s\n", fileVertexShader);
		fscanf(filePointer, "FS %s\n", fileFragmentShader);

		pShaders[i] = (Shaders*)malloc(sizeof(Shaders));
		p_ishaderInit[i] = pShaders[i]->Init(fileVertexShader, fileFragmentShader);
	}

	fclose(filePointer);

	delete filePath;
	delete fileVertexShader;
	delete fileFragmentShader;
}

int ResourceManager::GetShaderInitById(int Id)
{
	return p_ishaderInit[Id];
}

Model* ResourceManager::GetModelById(int Id)
{
	return pModels[Id];
}

Texture* ResourceManager::GetTextureById(int Id)
{
	return pTextures[Id];
}

Shaders* ResourceManager::GetShaderById(int Id)
{
	return pShaders[Id];
}

ResourceManager::~ResourceManager()
{
	for (int i = 0; i < inumModels; i++) 
	{
		delete pModels[i];
	}
	free(pModels);

	for (int i = 0; i < inumTextures; i++) 
	{
		free(pTextures[i]);
	}
	free(pTextures);

	for (int i = 0; i < inumShaders; i++) 
	{
		free(pShaders[i]);
	}

	free(pShaders);
	free(p_ishaderInit);
}
