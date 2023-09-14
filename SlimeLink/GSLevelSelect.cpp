#include "stdafx.h"
#include "GSLevelSelect.h"
#include "AudioManager.h"

GSLevelSelect::GSLevelSelect()
{
	Init("../SlimeLink/GSLevelSelect.txt", StateType::STATE_LEVEL_SELECT);
	AudioManager::GetInstance()->GetAudioById(6)->StopMusic();
	Vector3 levelPos = Vector3(200.0f, 200.0f, 0.0f);
	Vector3 levelRotation = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 levelScale = Vector3(150.0f, 150.0f, 1.0f);
	Vector3 levelWidthEach = Vector3(450.0f, 0.0f, 0.0f);
	Vector3 levelHeightEach = Vector3(0.0f, 320.0f, 0.0f);

	Vector3 trophyOffset = Vector3(-50.0f, 100.0f, 0.0f);
	Vector3 trophyWidthEach = Vector3(50.0f, 0.0f, 0.0f);

	// Create level select button and trophy pictures
	pSelectLevel = (SelectLevelButton**)malloc(sizeof(SelectLevelButton*) * iLevelPerPage);
	pTrophy = (Picture**)malloc(sizeof(Picture*) * 3 * iLevelPerPage);
	for (int i = 0; i < iRowPerPage; i++)
	{
		for (int j = 0; j < (iLevelPerPage / iRowPerPage); j++)
		{
			//Level select button
			pSelectLevel[i * 3 + j] = (SelectLevelButton*)malloc(sizeof(SelectLevelButton));

			*(pSelectLevel[i * 3 + j]) = SelectLevelButton(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(59 + i * 3 + j), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), levelPos + levelHeightEach * i + levelWidthEach * j, levelRotation, levelScale, 0, 1);
			pSelectLevel[i * 3 + j]->SetCurrentLevel(i * 3 + j + 1);

			//Trophy pictures
			for (int k = 0; k < 3; k++) {
				pTrophy[3 * (i * 3 + j) + k] = (Picture*)malloc(sizeof(Picture));

				*(pTrophy[3 * (i * 3 + j) + k]) = Picture(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(16), pCamera,
					ResourceManager::GetInstance()->GetShaderById(0), levelPos + levelHeightEach * i + levelWidthEach * j + trophyOffset + trophyWidthEach * k, levelRotation, levelScale / 3.0f, 0);
			}
		}
	}

	pPointOfLevel = new int[NUM_OF_LEVELS + 1];

	//If the file contains all score does not exists, create a new file with score of all levels = 0
	if (fopen("../Resources/Level/Level.txt", "r") == nullptr)
	{
		FILE* writePointer = fopen("../Resources/Level/Level.txt", "w");

		for (int i = 1; i <= NUM_OF_LEVELS; i++) {
			fprintf(writePointer, "%d\n", 0);
		}

		fclose(writePointer);
	}

	//Read point of every level and store into pointOfLevel
	FILE* filePointer;

	try
	{
		filePointer = fopen("../Resources/Level/Level.txt", "r");
	}
	catch (...)
	{
		printf("Cannot open score file\n");
	}

	for (int i = 1; i <= NUM_OF_LEVELS; i++) {
		fscanf(filePointer, "%d\n", &pPointOfLevel[i]);
	}

	fclose(filePointer);

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
	// NOTE: Delete select level square
	for (int i = 0; i < iLevelPerPage; i++) {
		free(pSelectLevel[i]);
	}
	free(pSelectLevel);

	// NOTE: Delete all trophy pictures
	for (int i = 0; i < 3 * iLevelPerPage; i++)
	{
		free(pTrophy[i]);
	}
	free(pTrophy);

	delete pPointOfLevel;

	GameStateBase::Exit();
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
	int* typeButton = new int;
	*typeButton = 0;

	// NOTE: check all button if it got click or not
	if (isPressed && pButtons != nullptr && pSelectLevel != nullptr)
	{
		for (int i = 0; i < iLevelPerPage; i++)
		{
			pSelectLevel[i]->MouseClick(x, y);
		}

		//Reset game, yes and no button
		for (int i = inumButtons - 3; i < inumButtons; i++)
		{
			if (pButtons == nullptr)
			{
				break;
			}

			if (pButtons[i]->getActive())
			{
				pButtons[i]->MouseClickResetGame(x, y, typeButton);
			}
		}

		//Back, next and prev button
		for (int i = 0; i < inumButtons - 3; i++)
		{
			pButtons[i]->MouseClick(x, y, &iCurrentPage, iSumPage);

			if (pButtons == nullptr) 
			{
				break;
			}
		}

		UpdateLevel();
	}

	// 1. Reset game is pressed
	// 2. Yes is pressed
	// 3. No is pressed
	if(*typeButton == 1)
	{
		SetResetGameUI(true);
	}
	else if (*typeButton == 2)
	{
		SetResetGameUI(false);

		//If yes (reset game progress), reset point array and inactivate all trophy
		for (int i = 0; i < NUM_OF_LEVELS + 1; i++)
		{
			pPointOfLevel[i] = 0;
		}

		for (int i = 0; i < 3 * iLevelPerPage; i++)
		{
			pTrophy[i]->setActive(false);
		}
	}
	else if (*typeButton == 3)
	{
		SetResetGameUI(false);
	}

	delete typeButton;
}

void GSLevelSelect::SetResetGameUI(bool status)
{
	//Set buttons
	for (int i = 0; i < inumButtons; i++)
	{
		if (pButtons[i]->getType() == YES || pButtons[i]->getType() == NO)
		{
			pButtons[i]->setActive(status);
		}
		else
		{
			pButtons[i]->setActive(!status);
		}
	}

	//Set pictures
	for (int i = inumPics - 2; i < inumPics; i++)
	{
		pPictures[i]->setActive(status);
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
	//Draw before opacity
	for (int i = 0; i < inumPics - 2; i++)
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

	for (int i = 0; i < inumButtons - 2; i++)
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

	//Draw after opacity
	for (int i = inumPics - 2; i < inumPics; i++)
	{
		if (pPictures[i]->getActive())
		{
			pPictures[i]->Draw();
		}
	}

	for (int i = inumButtons - 2; i < inumButtons; i++)
	{
		if (pButtons[i]->getActive())
		{
			pButtons[i]->Draw();
		}
	}
}