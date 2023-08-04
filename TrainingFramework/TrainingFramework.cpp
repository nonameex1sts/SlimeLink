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

}

void Key(ESContext* esContext, unsigned char key, bool bIsPressed)
{

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