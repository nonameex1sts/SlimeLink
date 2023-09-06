#pragma once
#pragma once
#include "GameStateBase.h"
#include "../Utilities/utilities.h"
#include "ResourceManager.h"
#include "Button.h"
#include "Picture.h"
#include "SelectLevelButton.h"
#include "Globals.h"

class GSLevelSelect : public GameStateBase
{
private:
	SelectLevelButton** pSelectLevel;
	Picture** pTrophy;
	int iLevelPerPage = 6;
	int iRowPerPage = 2;
	int iCurrentPage = 0;
	int iSumPage = NUM_OF_LEVELS / iLevelPerPage;

	int* pPointOfLevel;

public:
	GSLevelSelect();
	~GSLevelSelect();
	void Exit();
	void Pause();
	void Resume();
	void Update(GLfloat deltatime);
	void Key(int keyPressed);
	void MouseClick(int x, int y, bool isPressed);
	void MouseMove(int x, int y);
	void Draw();
	void UpdateLevel();
};