#pragma once
#include "GameStateBase.h"

class GSIntro : public GameStateBase 
{
public:
	GSIntro(StateType type);
	~GSIntro();
	void Init();
	void Exit();
	void Pause();
	void Resume();
	void Update(GLfloat deltatime);
	void Draw();
};