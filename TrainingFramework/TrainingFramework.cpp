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

int Init(ESContext* esContext)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//Initialize ResourceManager and SceneManager
	SceneManager::CreateInstance();

	glEnable(GL_DEPTH_TEST);

	//Creation of shaders and program 
	return 0;

}

void Draw(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw object
	SceneManager::GetInstance()->Draw();

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update(ESContext* esContext, float deltaTime)
{
	SceneManager::GetInstance()->Update(esContext, deltaTime, keyPressed);
}

void Key(ESContext* esContext, unsigned char key, bool bIsPressed)
{
	//Arrowkeys for movement, ASWD for rotation
	if (bIsPressed)
	{
		switch (key)
		{
		case KEY_MOVE_LEFT:
			keyPressed |= 1 << 0;
			break;
		case KEY_MOVE_FORWARD:
			keyPressed |= 1 << 1;
			break;
		case KEY_MOVE_RIGHT:
			keyPressed |= 1 << 2;
			break;
		case KEY_MOVE_BACKWARD:
			keyPressed |= 1 << 3;
			break;
		case KEY_LEFT:
			keyPressed |= 1 << 4;
			break;
		case KEY_UP:
			keyPressed |= 1 << 5;
			break;
		case KEY_RIGHT:
			keyPressed |= 1 << 6;
			break;
		case KEY_DOWN:
			keyPressed |= 1 << 7;
			break;
		default:
			break;
		}
	}
	else 
	{
		switch (key)
		{
		case KEY_MOVE_LEFT:
			keyPressed ^= 1 << 0;
			break;
		case KEY_MOVE_FORWARD:
			keyPressed ^= 1 << 1;
			break;
		case KEY_MOVE_RIGHT:
			keyPressed ^= 1 << 2;
			break;
		case KEY_MOVE_BACKWARD:
			keyPressed ^= 1 << 3;
			break;
		case KEY_LEFT:
			keyPressed ^= 1 << 4;
			break;
		case KEY_UP:
			keyPressed ^= 1 << 5;
			break;
		case KEY_RIGHT:
			keyPressed ^= 1 << 6;
			break;
		case KEY_DOWN:
			keyPressed ^= 1 << 7;
			break;
		default:
			break;
		}
	}
}

void Mouse(ESContext* esContext, int x, int y, bool bIsPressed)
{
	if (bIsPressed) 
	{
		printf("%d %d\n", x, y);
	}
}

void CleanUp()
{
	ResourceManager::DestroyInstance();
	SceneManager::DestroyInstance();
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
	esRegisterMouseFunc(&esContext, Mouse);

	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}