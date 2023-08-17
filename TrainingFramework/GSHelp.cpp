#include "stdafx.h"
#include "GSHelp.h"

GSHelp::GSHelp()
{
	GameStateBase::GameStateBase(StateType::STATE_HELP);
	iCurrentImage = 0;
	Init();
}

GSHelp::~GSHelp()
{
	Exit();
}

void GSHelp::Init()
{
	// NOTE: Load image
	// NOTE: Load button
	printf("GSHelp init\n");
}

void GSHelp::Exit()
{
	// NOTE: Delete image
	// NOTE: Delete button
	printf("GSHelp exit\n");
}

void GSHelp::Pause()
{
	// NOTE: blank
}

void GSHelp::Resume()
{
	// NOTE: blank
}

void GSHelp::Update(GLfloat deltatime)
{
	//NOTE: check current iCurrentImage to show that image
}

void GSHelp::Key(int iKeyPressed)
{
	// NOTE: blank
}

void GSHelp::MouseClick(int x, int y, bool isPressed)
{
	// NOTE: check each button if it got click or not
}

void GSHelp::MouseMove(int x, int y)
{
	// NOTE: blank
}

void GSHelp::Draw()
{
	// NOTE: Draw image
	// NOTE: Draw button
}