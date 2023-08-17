// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Globals.h"
#include <conio.h>
#include "GSPlay.h"

//unsigned char keyPressed = 0;
GSPlay* gsPlay;

int Init(ESContext* esContext)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//Initialize ResourceManager and SceneManager
	gsPlay = new GSPlay(1);

	//Creation of shaders and program 
	return 0;

}

void Draw(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw object
	gsPlay->Draw();

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update(ESContext* esContext, float deltaTime)
{
	gsPlay->Update(deltaTime);
}

void Key(ESContext* esContext, unsigned char key, bool bIsPressed)
{
	//Arrowkeys for movement, ASWD for rotation
	if (bIsPressed) 
	{
		gsPlay->Key(key);
	}
}

void MouseClick(ESContext* esContext, int x, int y, bool bIsPressed)
{
	gsPlay->MouseClick(x, y, bIsPressed);
}

void MouseMove(ESContext* esContext, int x, int y)
{
}

void CleanUp()
{
	delete gsPlay;
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
	esRegisterMouseFunc(&esContext, MouseClick);
	esRegisterMouseMoveFunc(&esContext, MouseMove);

	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}