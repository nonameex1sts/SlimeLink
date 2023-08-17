#include "stdafx.h"
#include "GSCredit.h"

GSCredit::GSCredit()
{
	GameStateBase::GameStateBase(StateType::STATE_CREDIT);
	Init();
}

GSCredit::~GSCredit()
{
	Exit();
}

void GSCredit::Init()
{
	// NOTE: Load images
	// NOTE: Load button
	printf("GSCredit init\n");
}

void GSCredit::Exit()
{
	// NOTE: Delete image
	// NOTE: Delete button
	printf("GSCredit exit\n");
}

void GSCredit::Pause()
{
	// NOTE: blank
}

void GSCredit::Resume()
{
	// NOTE: blank
}

void GSCredit::Update(GLfloat deltatime)
{
	//NOTE: blank
}

void GSCredit::Key(int iKeyPressed)
{
	// NOTE: blank
}

void GSCredit::MouseClick(int x, int y, bool isPressed)
{
	// NOTE: check back button if it got click or not
}

void GSCredit::MouseMove(int x, int y)
{
	// NOTE: blank
}

void GSCredit::Draw()
{
	// NOTE: Draw image
	// NOTE: Draw button
}