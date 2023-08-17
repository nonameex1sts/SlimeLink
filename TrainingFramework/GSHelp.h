#pragma once
#include "GameStateBase.h"
#include "../Utilities/utilities.h"

class GSHelp : public GameStateBase
{
private:
	// backgroundImage
	// helpImage[5]
	// button(nextImage, lastImage, back)
	int iCurrentImage;
public:
	GSHelp();
	~GSHelp();
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