#include "stdafx.h"
#include "GSLevelSelect.h"

GSLevelSelect::GSLevelSelect()
{
	GameStateBase::GameStateBase(StateType::STATE_LEVEL_SELECT);
	Init();
}

GSLevelSelect::~GSLevelSelect()
{
	Exit();
}

void GSLevelSelect::Init()
{
	// NOTE: Load image
	// NOTE: Load button
	printf("GSLevelSelect init\n");
}

void GSLevelSelect::Exit()
{
	// NOTE: Delete image
	// NOTE: Delete button
	printf("GSLevelSelect exit\n");
}

void GSLevelSelect::Pause()
{
	// NOTE: blank
}

void GSLevelSelect::Resume()
{
	// NOTE: blank
}

void GSLevelSelect::Update(GLfloat deltatime)
{
}

void GSLevelSelect::Key(int iKeyPressed)
{
	// NOTE: blank
}

void GSLevelSelect::MouseClick(int x, int y, bool isPressed)
{
	// NOTE: check each button if it got click or not
}

void GSLevelSelect::MouseMove(int x, int y)
{
	// NOTE: blank
}

void GSLevelSelect::Draw()
{
	// NOTE: Draw intro
}