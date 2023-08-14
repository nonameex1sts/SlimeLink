#include "stdafx.h"
#include "ResourceManager.h"
#include <string>

ResourceManager* ResourceManager::ms_pInstance = nullptr;

ResourceManager::ResourceManager()
{
	FILE* filePointer = fopen("../TrainingFramework/RM.txt", "r");
	int id;
	char* filePath = new char[50];

	//Load data form RM.txt and initialize models
	fscanf(filePointer, "#Models: %d\n", &numModels);
	models = new Model* [numModels];

	for (int i = 0; i < numModels; i++) {
		fscanf(filePointer, "ID %d\n", &id);
		fscanf(filePointer, "FILE %s\n", filePath);
		models[i] = new Model(filePath);
	}

	//Load data form RM.txt and initialize textures
	fscanf(filePointer, "#2D Textures: %d\n", &numTextures);
	textures = new Texture* [numTextures];

	for (int i = 0; i < numTextures; i++) {
		fscanf(filePointer, "ID %d\n", &id);
		fscanf(filePointer, "FILE %s\n", filePath);
		textures[i] = new Texture(filePath);
	}

	//Load data form RM.txt and initialize shaders
	char* fileVertexShader = new char[100];
	char* fileFragmentShader = new char[100];
	fscanf(filePointer, "#Shaders: %d\n", &numShaders);
	shaders = new Shaders* [numShaders];
	shaderInit = new int[numShaders];

	for (int i = 0; i < numShaders; i++) {
		fscanf(filePointer, "ID %d\n", &id);
		fscanf(filePointer, "VS %s\n", fileVertexShader);
		fscanf(filePointer, "FS %s\n", fileFragmentShader);
		shaders[i] = new Shaders();
		shaderInit[i] = shaders[i]->Init(fileVertexShader, fileFragmentShader);
	}

	fclose(filePointer);

	delete filePath;
	delete fileVertexShader;
	delete fileFragmentShader;
}

int ResourceManager::GetShaderInitById(int Id)
{
	return shaderInit[Id];
}

Model* ResourceManager::GetModelById(int Id)
{
	return models[Id];
}

Texture* ResourceManager::GetTextureById(int Id)
{
	return textures[Id];
}

Shaders* ResourceManager::GetShaderById(int Id)
{
	return shaders[Id];
}

ResourceManager::~ResourceManager()
{
	for (int i = 0; i < numModels; i++) {
		delete models[i];
	}
	delete models;

	for (int i = 0; i < numTextures; i++) {
		delete textures[i];
	}
	delete textures;

	for (int i = 0; i < numShaders; i++) {
		delete shaders[i];
	}
	delete shaders;
	delete shaderInit;
}
