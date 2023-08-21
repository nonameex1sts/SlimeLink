#include "stdafx.h"
#include "ElementManager.h"
#include <string>

ElementManager* ElementManager::ms_pInstance = nullptr;

ElementManager::ElementManager()
{
	FILE* filePointer = fopen("../TrainingFramework/RM.txt", "r");
	int id;
	char* filePath = new char[50];

	//Load data form RM.txt and initialize models
	fscanf(filePointer, "#Models: %d\n", &inumModels);
	pModels = new Model * [inumModels];

	for (int i = 0; i < inumModels; i++)
	{
		fscanf(filePointer, "ID %d\n", &id);
		fscanf(filePointer, "FILE %s\n", filePath);
		pModels[i] = new Model(filePath);
	}

	//Load data form RM.txt and initialize textures
	fscanf(filePointer, "#2D Textures: %d\n", &inumTextures);
	pTextures = new Texture * [inumTextures];

	for (int i = 0; i < inumTextures; i++)
	{
		fscanf(filePointer, "ID %d\n", &id);
		fscanf(filePointer, "FILE %s\n", filePath);
		pTextures[i] = new Texture(filePath);
	}

	//Load data form RM.txt and initialize shaders
	char* fileVertexShader = new char[100];
	char* fileFragmentShader = new char[100];
	fscanf(filePointer, "#Shaders: %d\n", &inumShaders);
	pShaders = new Shaders * [inumShaders];
	p_ishaderInit = new int[inumShaders];

	for (int i = 0; i < inumShaders; i++)
	{
		fscanf(filePointer, "ID %d\n", &id);
		fscanf(filePointer, "VS %s\n", fileVertexShader);
		fscanf(filePointer, "FS %s\n", fileFragmentShader);
		pShaders[i] = new Shaders();
		p_ishaderInit[i] = pShaders[i]->Init(fileVertexShader, fileFragmentShader);
	}

	fclose(filePointer);

	delete filePath;
	delete fileVertexShader;
	delete fileFragmentShader;
}

int ElementManager::GetShaderInitById(int Id)
{
	return p_ishaderInit[Id];
}

Model* ElementManager::GetModelById(int Id)
{
	return pModels[Id];
}

Texture* ElementManager::GetTextureById(int Id)
{
	return pTextures[Id];
}

Shaders* ElementManager::GetShaderById(int Id)
{
	return pShaders[Id];
}

ElementManager::~ElementManager()
{
	for (int i = 0; i < inumModels; i++)
	{
		delete pModels[i];
	}
	delete pModels;

	for (int i = 0; i < inumTextures; i++)
	{
		delete pTextures[i];
	}
	delete pTextures;

	for (int i = 0; i < inumShaders; i++)
	{
		delete pShaders[i];
	}

	delete pShaders;
	delete p_ishaderInit;
}
