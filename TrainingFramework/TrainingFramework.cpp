// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include "Model.h"
#include "Object.h"
#include "ResourceManager.h"
#include "SceneManager.h"

unsigned char keyPressed = 0;
ResourceManager* resourceManager;
SceneManager* sceneManager;

int Init(ESContext* esContext)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	resourceManager = new ResourceManager;
	sceneManager = new SceneManager(resourceManager);

	glEnable(GL_DEPTH_TEST);

	//Creation of shaders and program 
	return resourceManager->GetShaderInitById(0);

}

void Draw(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw object
	sceneManager->Draw();

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update(ESContext* esContext, float deltaTime)
{
	sceneManager->Update(esContext, deltaTime, keyPressed);
	keyPressed = 0;
}

void Key(ESContext* esContext, unsigned char key, bool bIsPressed)
{
	//Arrowkeys for movement, ASWD for rotation
	if (bIsPressed) {
		switch (key)
		{
		case 37:
			keyPressed += 1 << 0;
			break;
		case 38:
			keyPressed += 1 << 1;
			break;
		case 39:
			keyPressed += 1 << 2;
			break;
		case 40:
			keyPressed += 1 << 3;
			break;
		case 65:
			keyPressed += 1 << 4;
			break;
		case 87:
			keyPressed += 1 << 5;
			break;
		case 68:
			keyPressed += 1 << 6;
			break;
		case 83:
			keyPressed += 1 << 7;
			break;
		default:
			break;
		}
	}
}

void CleanUp()
{
	delete resourceManager;
	delete sceneManager;
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

	esInitContext(&esContext);

	esCreateWindow(&esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if (Init(&esContext) != 0)
		return 0;

	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, Key);

	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}