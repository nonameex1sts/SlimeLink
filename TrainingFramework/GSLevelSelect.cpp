#include "stdafx.h"
#include "GSLevelSelect.h"
#include "AudioManager.h"

GSLevelSelect::GSLevelSelect()
{
	Init("../TrainingFramework/GSLevelSelect.txt", StateType::STATE_LEVEL_SELECT);
	Vector3 levelPos = Vector3(200.0f, 200.0f, 0.0f);
	Vector3 levelRotation = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 levelScale = Vector3(150.0f, 150.0f, 1.0f);
	Vector3 levelWidthEach = Vector3(450.0f, 0.0f, 0.0f);
	Vector3 levelHeightEach = Vector3(0.0f, 320.0f, 0.0f);

	Vector3 trophyOffset = Vector3(-50.0f, 100.0f, 0.0f);
	Vector3 trophyWidthEach = Vector3(50.0f, 0.0f, 0.0f);

	// Create level select button
	pSelectLevel = new SelectLevelButton * [iLevelPerPage];
	pTrophy = new Picture * [iLevelPerPage * 3];
	for (int i = 0; i < iRowPerPage; i++)
	{
		for (int j = 0; j < (iLevelPerPage / iRowPerPage); j++)
		{
			pSelectLevel[i * 3 + j] = new SelectLevelButton(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(59 + i * 3 + j), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), levelPos + levelHeightEach * i + levelWidthEach * j, levelRotation, levelScale, 0, 1);
			pSelectLevel[i * 3 + j]->SetCurrentLevel(i * 3 + j + 1);

			for (int k = 0; k < 3; k++) {
				pTrophy[3 * (i * 3 + j) + k] = new Picture(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(43), pCamera,
					ResourceManager::GetInstance()->GetShaderById(0), levelPos + levelHeightEach * i + levelWidthEach * j + trophyOffset + trophyWidthEach * k, levelRotation, levelScale / 3.0f, 0);
			}
		}
	}

	pPointOfLevel = new int[NUM_OF_LEVELS + 1];

	//Read point of every level and store into pointOfLevel
	FILE* filePoiter = fopen("../Resources/Level/Level.txt", "r");

	for (int i = 1; i <= NUM_OF_LEVELS; i++) {
		fscanf(filePoiter, "%d\n", &pPointOfLevel[i]);
	}

	fclose(filePoiter);

	//Activate trophy pictures of first page based on scores read from file
	for (int i = 1; i <= iLevelPerPage; i++) {
		for (int j = 0; j < pPointOfLevel[i]; j++) {
			pTrophy[3 * (i - 1) + j]->setActive(true);
		}
	}
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

	for (int i = 0; i < 3 * iLevelPerPage; i++)
	{
		delete pTrophy[i];
	}
	delete pTrophy;

	delete pPointOfLevel;
}

void GSLevelSelect::Pause()
{
	// NOTE: blank
}

void GSLevelSelect::Resume()
{
	AudioManager::GetInstance()->GetAudioById(0)->PlayMusic();
	
	//Rewrite score array
	FILE* filePoiter = fopen("../Resources/Level/Level.txt", "r");

	for (int i = 1; i <= NUM_OF_LEVELS; i++) {
		fscanf(filePoiter, "%d\n", &pPointOfLevel[i]);
	}

	fclose(filePoiter);

	//Deactivate all trophy
	for (int i = 0; i < iLevelPerPage * 3; i++) {
		pTrophy[i]->setActive(false);
	}

	//Activate trophy pictures of current page based on scores read from file
	for (int i = 0; i < iLevelPerPage; i++)
	{
		for (int j = 0; j < pPointOfLevel[iCurrentPage * iLevelPerPage + i + 1]; j++) {
			pTrophy[3 * i + j]->setActive(true);
		}
	}
}

void GSLevelSelect::Update(GLfloat deltatime)
{
}

void GSLevelSelect::Key(int iKeyPressed)
{
	// NOTE: blank
}

// Update what level the button will go to base on which page is it and trophy of that button
void GSLevelSelect::UpdateLevel()
{
	//Deactivate all trophy
	for (int i = 0; i < iLevelPerPage * 3; i++) {
		pTrophy[i]->setActive(false);
	}

	for (int i = 0; i < iLevelPerPage; i++)
	{
		pSelectLevel[i]->SetCurrentLevel(iCurrentPage * iLevelPerPage + i + 1);
		pSelectLevel[i]->SetTexture(ResourceManager::GetInstance()->GetTextureById(58 + iCurrentPage * iLevelPerPage + i + 1));

		//Activate trophy pictures of current page based on scores read from file
		for (int j = 0; j < pPointOfLevel[iCurrentPage * iLevelPerPage + i + 1]; j++) {
			pTrophy[3 * i + j]->setActive(true);
		}
	}
}

void GSLevelSelect::MouseClick(int x, int y, bool isPressed)
{
	// NOTE: check all button if it got click or not
	if (isPressed && pButtons != nullptr && pSelectLevel != nullptr)
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
	}
}

void GSLevelSelect::MouseMove(int x, int y)
{
	for (int i = 0; i < inumButtons; i++)
	{
		pButtons[i]->MouseMove(x, y);
	}
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

	for (int i = 0; i < 3 * iLevelPerPage; i++) 
	{
		if (pTrophy[i]->getActive()) 
		{
			pTrophy[i]->Draw();
		}
	}
}