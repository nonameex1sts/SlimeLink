#include "stdafx.h"
#include "GameStateBase.h"
#include "GSMenu.h"
#include "GSHelp.h"
#include "GSCredit.h"
#include "GSLevelSelect.h"
#include "GSPlay.h"
#include "GSPause.h"

GameStateBase::GameStateBase()
{
}

GameStateBase::GameStateBase(StateType e_type)
{
	this->e_type = e_type;
}

GameStateBase::~GameStateBase()
{
}

void GameStateBase::Init()
{
}

void GameStateBase::Exit()
{
}

void GameStateBase::Pause()
{
}

void GameStateBase::Resume()
{
}

void GameStateBase::Update(GLfloat deltatime)
{
}

void GameStateBase::Key(int iKeyPressed)
{
}

void GameStateBase::MouseClick(int x, int y, bool isPressed)
{
}

void GameStateBase::MouseMove(int x, int y)
{
}

void GameStateBase::Draw()
{
}

StateType GameStateBase::GetStateType()
{
	return e_type;
}

GameStateBase* GameStateBase::CreateState(StateType type)
{
	GameStateBase* res;

	switch (type) {
	case StateType::STATE_MENU:
		res = new GSMenu;
		break;
	case StateType::STATE_LEVEL_SELECT:
		res = new GSLevelSelect;
	case StateType::STATE_HELP:
		res = new GSHelp;
		break;
	case StateType::STATE_CREDIT:
		res = new GSCredit;
		break;
	case StateType::STATE_PAUSE:
		res = new GSPause;
		break;
	default:
		res = nullptr;
		break;
	}

	return res;
}

GameStateBase* GameStateBase::CreateStatePlay(int ilevelNumber)
{
	GameStateBase* res;
	res = new GSPlay(ilevelNumber);
	return res;
}
