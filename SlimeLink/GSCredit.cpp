#include "stdafx.h"
#include "GSCredit.h"

GSCredit::GSCredit()
{
	Init("../SlimeLink/GSCredit.txt", StateType::STATE_CREDIT);
	slime = new Animation(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(12), pCamera,
		ResourceManager::GetInstance()->GetShaderById(1), Vector3(674.0f, 125.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(45.0f, 45.0f, 0.0f), 6, 1, 0, 0.1);
}

GSCredit::~GSCredit()
{
	Exit();
	delete slime;
}

void GSCredit::Update(GLfloat deltatime)
{
	slime->Update(deltatime);
}

void GSCredit::MouseClick(int x, int y, bool isPressed)
{
	// NOTE: check all button if it got click or not
	if (isPressed && pButtons != nullptr)
	{
		for (int i = 0; i < inumButtons; i++)
		{
			pButtons[i]->MouseClick(x, y, isPressed);

			if (pButtons == nullptr)
			{
				break;
			}
		}
	}
}

void GSCredit::MouseMove(int x, int y)
{
	for (int i = 0; i < inumButtons; i++)
	{
		pButtons[i]->MouseMove(x, y);
	}
}

void GSCredit::Draw()
{
	for (int i = 0; i < inumPics; i++)
	{
		if (pPictures[i]->getActive())
		{
			pPictures[i]->Draw();
		}
	}
	// BGM and SFX button switch to on and off
	for (int i = 0; i < inumButtons; i++)
	{
		if (pButtons[i]->getActive())
		{
			pButtons[i]->Draw();
		}
	}
	slime->Draw();
}