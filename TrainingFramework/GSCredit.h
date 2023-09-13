#pragma once
#include "GameStateBase.h"
#include "../Utilities/utilities.h"
#include "ResourceManager.h"
#include "Button.h"
#include "Picture.h"
#include "Animation.h"


class GSCredit : public GameStateBase
{
private:
	Animation* slime;
public:
	GSCredit();
	~GSCredit();
	void Update(GLfloat deltatime);
	void MouseClick(int x, int y, bool isPressed);
	void MouseMove(int x, int y);
	void Draw();
};