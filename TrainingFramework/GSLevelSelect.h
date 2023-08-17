#pragma once
#pragma once
#include "GameStateBase.h"
#include "../Utilities/utilities.h"

class GSLevelSelect : public GameStateBase
{
private:
	// backgroundImage
	// levelButton**
	// backButton
	// nextPageButton, lastPageButton
	int iLevelSelect = 0;
public:
	GSLevelSelect();
	~GSLevelSelect();
	void Init();
	void Exit();
	void Pause();
	void Resume();
	void Update(GLfloat deltatime);
	void Key(int keyPressed);
	void MouseClick(int x, int y, bool isPressed);
	void MouseMove(int x, int y);
	void Draw();
};