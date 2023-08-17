#include "stdafx.h"
#include "GSMenu.h"

GSMenu::GSMenu()
{
	GameStateBase::GameStateBase(StateType::STATE_MENU);
	Init();
}

GSMenu::~GSMenu()
{
	Exit();
}

void GSMenu::Init()
{
	// NOTE: Load image
	// NOTE: Load button
	printf("GSMenu init\n");
}

void GSMenu::Exit()
{
	// NOTE: Delete button
	printf("GSMenu exit\n");
}

void GSMenu::Pause()
{
	// NOTE: blank
}

void GSMenu::Resume()
{
	// NOTE: blank
}

void GSMenu::Update(GLfloat deltatime)
{
}

void GSMenu::Key(int iKeyPressed)
{
	// NOTE: blank
}

void GSMenu::MouseClick(int x, int y, bool isPressed)
{
	if (isPressed)
	{
		for (int i = 0; i < static_cast<int>(ButtonType::NUMBER_OF_BUTTONS); i++) 
		{
			// NOTE:: Check if that button is clicked
		}
	}
}

void GSMenu::MouseMove(int x, int y)
{
	// NOTE: blank
}

void GSMenu::Draw()
{
	// NOTE: Draw image
	// NOTE: Draw button
}