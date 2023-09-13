#pragma once
#include "../Utilities/utilities.h"
#include "GameStateBase.h"
#include <stack>

class GameStateMachine {
private:
	static GameStateMachine* ms_pInstance;
	std::stack<GameStateBase*> m_stateStack;
	GameStateBase* p_activeState;
	GameStateBase* p_nextState;
	GameStateMachine();
	~GameStateMachine();

public:
	static void CreateInstance()
	{
		if (ms_pInstance == nullptr)
			ms_pInstance = new GameStateMachine;
	};

	static GameStateMachine* GetInstance()
	{
		return ms_pInstance;
	};

	static void DestroyInstance()
	{
		if (ms_pInstance != nullptr)
		{
			delete ms_pInstance;
			ms_pInstance = nullptr;
		}
	};

	void ChangeState(GameStateBase* state);
	GameStateBase* ChangeState(StateType type);
	GameStateBase* ChangeStatePlay(int ilevelNumber);
	void PushState(StateType type, int ilevelNumber);
	void PopState();
	void PopState(StateType type);
	void PerformStateChange();
	GameStateBase* GetActiveState();
};