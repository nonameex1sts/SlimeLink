#include "stdafx.h"
#include "GSLevelSelect.h"
#include "AudioManager.h"

GSLevelSelect::GSLevelSelect()
{
	Init("../TrainingFramework/GSLevelSelect.txt", "GSLevelSelect");
	Vector3 levelPos = Vector3(200.0f, 180.0f, 0.0f);
	Vector3 levelRotation = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 levelScale = Vector3(150.0f, 150.0f, 1.0f);
	Vector3 levelWidthEach = Vector3(450.0f, 0.0f, 0.0f);
	Vector3 levelHeightEach = Vector3(0.0f, 350.0f, 0.0f);

	pSelectLevel = new SelectLevelButton * [6];
	for (int i = 0; i < iRowPerPage; i++)
	{
		for (int j = 0; j < (iLevelPerPage / iRowPerPage); j++)
		{
			pSelectLevel[i * 3 + j] = new SelectLevelButton(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(0), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), levelPos + levelHeightEach * i + levelWidthEach * j, levelRotation, levelScale, 0, 1);
			pSelectLevel[i * 3 + j]->SetCurrentLevel(i * 3 + j + 1);
		}
	}
	GameStateBase::GameStateBase(StateType::STATE_LEVEL_SELECT);
}

GSLevelSelect::~GSLevelSelect()
{
	Exit();
}

void GSLevelSelect::Exit()
{
	// NOTE: Delete camera
	delete pCamera;
	// NOTE: Delete picture
	for (int i = 0; i < inumPics; i++) {
		delete pPictures[i];
	}
	delete pPictures;
	// NOTE: Delete select level square
	for (int i = 0; i < iLevelPerPage; i++) {
		delete pSelectLevel[i];
	}
	delete pSelectLevel;
	// NOTE: Delete button
	for (int i = 0; i < inumButtons; i++) {
		delete pButtons[i];
	}
	delete pButtons;
	printf("GSLevelSelect exit\n");
}

void GSLevelSelect::Pause()
{
	printf("GSLevelSelect pause\n");
	// NOTE: blank
}

void GSLevelSelect::Resume()
{
	AudioManager::GetInstance()->GetAudioById(0)->PlayMusic();
	printf("GSLevelSelect resume\n");
	// NOTE: blank
}

void GSLevelSelect::Update(GLfloat deltatime)
{
}

void GSLevelSelect::Key(int iKeyPressed)
{
	// NOTE: blank
}

// Update what level the button will go to base on which page is it
void GSLevelSelect::UpdateLevel()
{
	for (int i = 0; i < iLevelPerPage; i++)
	{
		pSelectLevel[i]->SetCurrentLevel(iCurrentPage * iLevelPerPage + i + 1);
	}
}

void GSLevelSelect::MouseClick(int x, int y, bool isPressed)
{
	// NOTE: check all button if it got click or not
	if (isPressed)
	{
		for (int i = 0; i < iLevelPerPage; i++)
		{
			pSelectLevel[i]->MouseClick(x, y);
		}
		for (int i = 0; i < inumButtons; i++)
		{
			pButtons[i]->MouseClick(x, y, &iCurrentPage, iSumPage);
		}
		UpdateLevel();
		printf("%d\n", iCurrentPage);
	}
}

void GSLevelSelect::MouseMove(int x, int y)
{
	// NOTE: blank
}

void GSLevelSelect::Draw()
{
	for (int i = 0; i < inumPics; i++)
	{
		if (pPictures[i]->getActive())
		{
			pPictures[i]->Draw();
		}
	}
	for (int i = 0; i < iLevelPerPage; i++) {
		if (pSelectLevel[i]->getActive())
		{
			pSelectLevel[i]->Draw();
		}
	}
	for (int i = 0; i < inumButtons; i++)
	{
		if (pButtons[i]->getActive())
		{
			pButtons[i]->Draw();
		}
	}
}