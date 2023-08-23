// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Globals.h"
#include <conio.h>
#include "GSPlay.h"
#include "GameStateMachine.h"
#include "ResourceManager.h"
#include "SFML/Audio.hpp"

sf::Music music;

int Init(ESContext* esContext)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Initialize GameStateMachine
	GameStateMachine::CreateInstance();

	//Creation of shaders and program 
	return 0;

}

void Draw(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw object of active state
	GameStateMachine::GetInstance()->GetActiveState()->Draw();

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update(ESContext* esContext, float deltaTime)
{
	// Check for stage change
	GameStateMachine::GetInstance()->PerformStateChange();

	// Update active state
	GameStateMachine::GetInstance()->GetActiveState()->Update(deltaTime);
}

void Key(ESContext* esContext, unsigned char key, bool bIsPressed)
{
	//Arrowkeys for movement, ASWD for rotation
	if (bIsPressed) 
	{
		GameStateMachine::GetInstance()->GetActiveState()->Key(key);
	}
}

void MouseClick(ESContext* esContext, int x, int y, bool bIsPressed)
{
	GameStateMachine::GetInstance()->GetActiveState()->MouseClick(x, y, bIsPressed);
}

void MouseMove(ESContext* esContext, int x, int y)
{
}

void CleanUp()
{
	GameStateMachine::DestroyInstance();
	music.stop();
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (!music.openFromFile("../Resources/Music/test.wav"))
	{
		printf("Error\n");
	}
	if (!music.openFromFile("../Resources/Music/test2.wav"))
	{
		printf("Error\n");
	}
	music.setVolume(40);
	music.play();
	ESContext esContext;

	esInitContext(&esContext);

	esCreateWindow(&esContext, "Connected", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

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