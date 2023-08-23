#pragma once
#include "GameStateBase.h"
#include "../Utilities/utilities.h"
#include "Button.h"
#include "Picture.h"

class GSMenu : public GameStateBase
{
private:
	Camera* pCamera;
	int inumButtons;
	int inumPics;
	Button** pButtons;
	Picture** pPictures;
	// Image
	// Sound setting (SFX, Background music)
public:
	GSMenu();
	~GSMenu();
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