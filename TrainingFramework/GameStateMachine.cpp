#include "stdafx.h"
#include "GameStateMachine.h"
#include "GSIntro.h"

GameStateMachine* GameStateMachine::ms_pInstance = nullptr;

GameStateMachine::GameStateMachine()
{
	p_activeState = new GSIntro;
	m_stateStack.push(p_activeState);
	p_nextState = nullptr;
}

GameStateMachine::~GameStateMachine()
{
	//Empty stack
	while (!m_stateStack.empty()) {
		delete m_stateStack.top();
		m_stateStack.pop();
	}
}

void GameStateMachine::ChangeState(GameStateBase* state)
{
	p_nextState = state;
}

GameStateBase* GameStateMachine::ChangeState(StateType type)
{
	GameStateBase* newState = p_activeState->CreateState(type);
	ChangeState(newState);
	return newState;
}

GameStateBase* GameStateMachine::ChangeStatePlay(int ilevelNumber)
{
	GameStateBase* newState = p_activeState->CreateStatePlay(ilevelNumber);
	ChangeState(newState);
	return newState;
}

void GameStateMachine::PushState(StateType type, int ilevelNumber)
{
	GameStateBase* newState;

	//If new stage is Play, init with level number; otherwise init normally
	if (type == StateType::STATE_PLAY) {
		newState = ChangeStatePlay(ilevelNumber);
	}
	else {
		newState = ChangeState(type);
	}

	m_stateStack.push(newState);
}

void GameStateMachine::PopState()
{
	delete p_activeState;
	m_stateStack.pop();
	p_activeState = m_stateStack.top();
	p_activeState->Resume();
}

void GameStateMachine::PopState(StateType type)
{
	//printf("%d\n", type);
	do 
	{
		delete p_activeState;
		m_stateStack.pop();
		p_activeState = m_stateStack.top();
		//printf("%d\n", p_activeState->GetStateType());
	} 
	while (p_activeState->GetStateType() !=  type);

	p_activeState->Resume();
}

void GameStateMachine::PerformStateChange()
{
	if (p_nextState != nullptr) {
		if (p_activeState->GetStateType() == StateType::STATE_INTRO) {
			delete p_activeState;
			
		}

		p_activeState->Pause();
		p_activeState = m_stateStack.top();
		p_nextState = nullptr;
	}
}

GameStateBase* GameStateMachine::GetActiveState()
{
	return p_activeState;
}
