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

int KeyPressed = 0;
Object* object;

int Init(ESContext* esContext)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//Initialize object with model, texture and shader
	object = new Object("../Resources/Models/Woman1.nfg", "../Resources/Textures/Woman1.tga");

	glEnable(GL_DEPTH_TEST);

	//Creation of shaders and program 
	return object->shaderInit;

}

void Draw(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw object
	object->Draw();

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update(ESContext* esContext, float deltaTime)
{
	if (KeyPressed != 0) {
		object->camera->Inputs(deltaTime, KeyPressed);
	}
	KeyPressed = 0;
}

void Key(ESContext* esContext, unsigned char key, bool bIsPressed)
{
	if (bIsPressed) {
		switch (key)
		{
		case 37:
			KeyPressed += 1 << 0;
			break;
		case 38:
			KeyPressed += 1 << 1;
			break;
		case 39:
			KeyPressed += 1 << 2;
			break;
		case 40:
			KeyPressed += 1 << 3;
			break;
		case 65:
			KeyPressed += 1 << 4;
			break;
		case 87:
			KeyPressed += 1 << 5;
			break;
		case 68:
			KeyPressed += 1 << 6;
			break;
		case 83:
			KeyPressed += 1 << 7;
			break;
		default:
			break;
		}
	}
}

void CleanUp()
{
	object->Cleanup();
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