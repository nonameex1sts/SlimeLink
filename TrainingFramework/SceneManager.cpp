#include "stdafx.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include <string>

SceneManager* SceneManager::ms_pInstance = nullptr;

SceneManager::SceneManager(int ilevelNumber) {
	ResourceManager::CreateInstance();

	//Read map file
	std::string link = "../Resources/Level/map" + std::to_string(ilevelNumber) + ".txt";
	FILE* filePointer = fopen(link.c_str(), "r");

	//Initialize camera
	float fovY, nearPlane, farPlane, speed;
	fscanf(filePointer, "#CAMERA\n");
	fscanf(filePointer, "NEAR %f\n", &nearPlane);
	fscanf(filePointer, "FAR %f\n", &farPlane);
	fscanf(filePointer, "FOV %f\n", &fovY);
	fscanf(filePointer, "SPEED %f\n", &speed);
	pCamera = new Camera(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), fovY, nearPlane, farPlane, speed);

	//Width height of the map
	fscanf(filePointer, "Width: %d\n", &iWidth);
	fscanf(filePointer, "Height: %d\n", &iHeight);
	fscanf(filePointer, "Horizontal wall: %d\n", &iNumHorizontalWall);
	fscanf(filePointer, "Player: %d\n", &iNumPlayer);
	fscanf(filePointer, "Target: %d\n", &iNumTarget);
	fscanf(filePointer, "Spawn: %d\n", &iNumSpawn);

	//O - can move, 1 - cannot move, 2 - left wall, 3 - right wall
	p_imapType = new int* [iWidth];
	for (int i = 0; i < iWidth; i++) {
		p_imapType[i] = new int[iHeight];
	}

	pObjects = new Object * [iWidth * iHeight];
	pHorizontalWall = new Object * [iNumHorizontalWall];
	pPlayer = new Player * [iNumPlayer + iNumSpawn];
	pTargetPosition = new Vector3[iNumTarget];
	pSpawnPosition = new Vector3[iNumSpawn];

	int iHorizontalWallCounter = 0, iPlayerCounter = 0, iTargetCounter = 0, iSpawnCounter = 0;
	Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 scale = Vector3(SQUARE_SIZE, SQUARE_SIZE, 1.0f);

	for (int i = 0; i < iWidth * iHeight; i++) {
		int imapType;
		fscanf(filePointer, "%d ", &imapType);

		Vector3 position = Vector3(SQUARE_SIZE/2, SQUARE_SIZE/2, 0.0f);
		position.x += SQUARE_SIZE * (i % iWidth);
		position.y += SQUARE_SIZE * (i / iWidth);

		if (imapType <= 1  )
		{
			//Wall
			pObjects[i] = new Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(imapType), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			p_imapType[i % iWidth][i / iWidth] = imapType;
		}

		if ((imapType >= 6 && imapType <= 9) || imapType == 13)
		{
			p_imapType[i % iWidth][i / iWidth] = 1;

			//Wall
			pObjects[i] = new Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(imapType), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);
		}

		if (imapType == 2)
		{
			p_imapType[i % iWidth][i / iWidth] = 0;
			//Player
			pObjects[i] = new Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(0), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			pPlayer[iPlayerCounter] = new Player(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(imapType), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale, true);

			iPlayerCounter++;
		}

		if (imapType == 10)
		{
			p_imapType[i % iWidth][i / iWidth] = 2;

			//Wall
			pObjects[i] = new Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(0), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			pHorizontalWall[iHorizontalWallCounter] = new Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(imapType), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			iHorizontalWallCounter++;
		}

		if (imapType == 11)
		{
			p_imapType[i % iWidth][i / iWidth] = 3;

			//Wall
			pObjects[i] = new Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(0), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			pHorizontalWall[iHorizontalWallCounter] = new Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(imapType), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			iHorizontalWallCounter++;
		}

		if (imapType == 12)
		{
			p_imapType[i % iWidth][i / iWidth] = 0;

			pObjects[i] = new Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(0), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			//"Sleep" player
			pPlayer[iPlayerCounter] = new Player(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(imapType), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale, false);

			iPlayerCounter++;
		}

		if (imapType == 22)
		{
			p_imapType[i % iWidth][i / iWidth] = 0;

			pTargetPosition[iTargetCounter] = position;
			iTargetCounter++;

			//Target
			pObjects[i] = new Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(imapType), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);
		}

		if (imapType == 23)
		{
			p_imapType[i % iWidth][i / iWidth] = 0;

			pSpawnPosition[iSpawnCounter] = position;
			iSpawnCounter++;

			//Target
			pObjects[i] = new Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(imapType), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);
		}
	}

	fscanf(filePointer, "Star: %f %f %f\n", &star.x, &star.y, &star.y);

	fclose(filePointer);
}

void SceneManager::Update(float deltaTime)
{
}

void SceneManager::Key(unsigned char keyPressed)
{
	//Player movement
	if (!hasEnded) 
	{
		for (int i = 0; i < iNumPlayer; i++) {
			pPlayer[i]->Key(keyPressed);
		}
	}

	//Wake up inactive player
	for (int i = 0; i < iNumPlayer; i++) 
	{
		if (pPlayer[i]->GetActiveStatus()) 
		{
			for (int j = 0; j < iNumPlayer; j++) 
			{
				if (pPlayer[i]->CheckCloseObject(*pPlayer[j])) 
				{
					pPlayer[j]->SetActiveStatus(true);
					pPlayer[j]->SetTexture(*pPlayer[i]);
				}
			}
		}
	}

	for (int i = 0; i < iNumPlayer; i++)
	{
		pPlayer[i]->SetMoveRightStatus(true);
		pPlayer[i]->SetMoveLeftStatus(true);
		pPlayer[i]->SetMoveDownStatus(true);
		pPlayer[i]->SetMoveUpStatus(true);

		if (pPlayer[i]->GetActiveStatus())
		{
			Vector3 coordinate = pPlayer[i]->GetCoordinate();

			if ((p_imapType[(int)coordinate.x][(int)coordinate.y] == 3))
			{
				pPlayer[i]->SetMoveRightStatus(false);
			}
			else if (p_imapType[(int)coordinate.x + 1][(int)coordinate.y] == 1) 
			{
				pPlayer[i]->SetMoveRightStatus(false);
			}

			if ((p_imapType[(int)coordinate.x][(int)coordinate.y] == 2))
			{
				pPlayer[i]->SetMoveLeftStatus(false);
			}
			else if (p_imapType[(int)coordinate.x - 1][(int)coordinate.y] == 1) 
			{
				pPlayer[i]->SetMoveLeftStatus(false);
			}

			if (p_imapType[(int)coordinate.x][(int)coordinate.y + 1] == 1)
			{
				pPlayer[i]->SetMoveDownStatus(false);
			}

			if (p_imapType[(int)coordinate.x][(int)coordinate.y - 1] == 1)
			{
				pPlayer[i]->SetMoveUpStatus(false);
			}
		}
	}

	for (int i = 0; i < iNumSpawn && isSpawnActive; i++)
	{
		for (int j = 0; j < iNumPlayer && isSpawnActive; j++)
		{
			if (pPlayer[j]->GetActiveStatus() && pPlayer[j]->CheckPosition(pSpawnPosition[i]))
			{
				Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f);
				Vector3 scale = Vector3(SQUARE_SIZE, SQUARE_SIZE, 1.0f);
				for (int k = 0; k < iNumSpawn; k++)
				{
					pPlayer[iNumPlayer + k] = new Player(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(2), pCamera,
						ResourceManager::GetInstance()->GetShaderById(0), pSpawnPosition[k], rotation, scale, true);
				}
				iNumPlayer += iNumSpawn;

				for (int k = 0; k < iWidth * iHeight; k++)
				{
					for (int l = 0; l < iNumSpawn; l++)
					{
						if (pObjects[k]->CheckPosition(pSpawnPosition[l]))
						{
							pObjects[k]->SetTexture(ResourceManager::GetInstance()->GetTextureById(24));
						}
					}
				}

				isSpawnActive = false;
			}
		}
	}

	int iNumberTargetReached = 0, iNumberActivePlayerReached = 0, iNumberActivePlayer = 0;;
	for (int i = 0; i < iNumTarget; i++) 
	{
		for (int j = 0; j < iNumPlayer; j++) 
		{
			if (pPlayer[j]->GetActiveStatus() && pPlayer[j]->CheckPosition(pTargetPosition[i]))
			{
				iNumberTargetReached++;
				break;
			}
		}
	}

	for (int i = 0; i < iNumPlayer; i++) {
		if (pPlayer[i]->GetActiveStatus()) 
		{
			iNumberActivePlayer++;
			for (int j = 0; j < iNumTarget; j++) {
				if (pPlayer[i]->CheckPosition(pTargetPosition[j])) 
				{
					iNumberActivePlayerReached++;
				}
			}
		}
	}

	if(iNumberTargetReached == iNumTarget && iNumberActivePlayer == iNumberActivePlayerReached)
	{
		hasEnded = true;
		printf("Win\n");
	}
}

void SceneManager::Draw()
{
	for (int i = 0; i < iWidth * iHeight; i++)
	{
		pObjects[i]->Draw();
	}

	for (int i = 0; i < iNumPlayer; i++) 
	{
		pPlayer[i]->Draw();
	}

	for (int i = 0; i < iNumHorizontalWall; i++) 
	{
		pHorizontalWall[i]->Draw();
	}
}

SceneManager::~SceneManager()
{
	for (int i = 0; i < iWidth * iHeight; i++)
	{
		delete pObjects[i];
	}
	delete pObjects;

	for (int i = 0; i < iWidth; i++)
	{
		delete p_imapType[i];
	}
	delete p_imapType;

	for (int i = 0; i < iNumHorizontalWall; i++)
	{
		delete pHorizontalWall[i];
	}
	delete pHorizontalWall;
	
	for (int i = 0; i < iNumPlayer; i++) 
	{
		delete pPlayer[i];
	}
	delete pPlayer;
	
	delete pTargetPosition;
	delete pSpawnPosition;
	delete pCamera;
}