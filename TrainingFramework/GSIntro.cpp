#include "stdafx.h"
#include "GSIntro.h"

GSIntro::GSIntro()
{
	GameStateBase::GameStateBase(StateType::STATE_INTRO);
	Init();
}

GSIntro::~GSIntro()
{
	Exit();
}

void GSIntro::Init() 
{
	// NOTE: Load image
	printf("GSIntro init\n");
}

void GSIntro::Exit()
{
	// NOTE: Delete image
	printf("GSIntro exit\n");
}

void GSIntro::Pause()
{
	// NOTE: blank
}

void GSIntro::Resume()
{
	// NOTE: blank
}

void GSIntro::Update(GLfloat deltatime)
{
	if (deltatime > fTime)
	{
		// NOTE: Get menu state
	}
}

void GSIntro::Key(int iKeyPressed)
{
	// NOTE: blank
}

void GSIntro::MouseClick(int x, int y, bool isPressed)
{
	// NOTE: blank
}

void GSIntro::MouseMove(int x, int y)
{
	// NOTE: blank
}

void GSIntro::Draw()
{
	// NOTE: Draw intro
}