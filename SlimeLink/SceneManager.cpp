#include "stdafx.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include <string>
#include "AudioManager.h"

SceneManager* SceneManager::ms_pInstance = nullptr;

SceneManager::SceneManager(int ilevelNumber) {
	ResourceManager::CreateInstance();

	this->iLevelNumber = ilevelNumber;

	//Read map file
	std::string link = "../Resources/Level/map" + std::to_string(ilevelNumber) + ".txt";
	FILE* filePointer;

	try
	{
		filePointer = fopen(link.c_str(), "r");
	}
	catch (...)
	{
		printf("Cannot open scene manager file");
	}

	//Initialize camera
	float fovY, nearPlane, farPlane, speed;
	fscanf(filePointer, "#CAMERA\n");
	fscanf(filePointer, "NEAR %f\n", &nearPlane);
	fscanf(filePointer, "FAR %f\n", &farPlane);
	fscanf(filePointer, "FOV %f\n", &fovY);
	fscanf(filePointer, "SPEED %f\n", &speed);
	pCamera = new Camera(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), fovY, nearPlane, farPlane, speed);

	//Attributes of the map
	fscanf(filePointer, "Width: %d\n", &iWidth);
	fscanf(filePointer, "Height: %d\n", &iHeight);
	fscanf(filePointer, "Horizontal wall: %d\n", &iNumHorizontalWall);
	fscanf(filePointer, "Player: %d\n", &iNumPlayer);
	fscanf(filePointer, "Enemy: %d\n", &iNumEnemy);
	fscanf(filePointer, "Target: %d\n", &iNumTarget);
	fscanf(filePointer, "Spawn: %d\n", &iNumSpawn);
	fscanf(filePointer, "Obstacle: %d\n", &iNumObstacle);

	//Map's logic matrix: O - can move, 1 - cannot move, 2 - left wall, 3 - right wall
	p_imapType = (int**)malloc(sizeof(int*) * iWidth);
	for (int i = 0; i < iWidth; i++) {
		p_imapType[i] = (int*)malloc(sizeof(int) * iHeight);
	}

	//Initialize objects, walls, players, enemies, spawns and targets
	pObstacles = (Animation**)malloc(sizeof(Animation*) * iNumObstacle);
	pObjects = (Object**)malloc(sizeof(Object*) * iWidth * iHeight);		//title map
	pHorizontalWall = (Object**)malloc(sizeof(Object*) * iNumHorizontalWall);
	pPlayer = (Player**)malloc(sizeof(Player*) * (iNumPlayer + iNumSpawn));
	pEnemy = (Enemy**)malloc(sizeof(Enemy*) * iNumEnemy);
	pTargetPosition = (Vector3*)malloc(sizeof(Vector3) * iNumTarget);
	pSpawnPosition = (Vector3*)malloc(sizeof(Vector3) * iNumSpawn);

	//Index counter
	int iHorizontalWallCounter = 0, iPlayerCounter = 0, iEnemyCounter = 0, iTargetCounter = 0, iSpawnCounter = 0, iObstacleCounter = 0;

	//Rotation and scale of objects and players
	Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 scale = Vector3(SQUARE_SIZE, SQUARE_SIZE, 1.0f);

	/*
		1. wall
		2. blank
		6, 7, 8, 9. corner
		14, 15, 16, 15 small conner
		10. left wall
		11. right wal
		44. player
		12. sleep player
		13. obsticle
		20. left wall with obsticle
		21. right wall with obsticle
		22. target
		23. spawn
		24. player with spawn
		44. wake player
		85. torch
		45. enemy - follow and block player
	*/

	for (int i = 0; i < iWidth * iHeight; i++) {
		int imapType;
		fscanf(filePointer, "%d ", &imapType);

		//Calculate position of the current object
		Vector3 position = Vector3(SQUARE_SIZE/2, SQUARE_SIZE/2, 0.0f);
		position.x += SQUARE_SIZE * (i % iWidth);
		position.y += SQUARE_SIZE * (i / iWidth);

		//Transalate 1D[i] array into 2D array[width][height]: width = i % iWidth, height = i / iWidth
		if (imapType == 0) // FLOOR
		{
			p_imapType[i % iWidth][i / iWidth] = imapType;

			//Path
			pObjects[i] = (Object*) malloc(sizeof(Object));

			*(pObjects[i]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(2), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);
		}

		if (imapType == 1) // HORIZONTAL WALL
		{
			p_imapType[i % iWidth][i / iWidth] = imapType;

			pObjects[i] = (Object*)malloc(sizeof(Object));

			//Path
			*(pObjects[i]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(1), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);
		}

		if (imapType >= 6 && imapType <= 9) // CORNER
		{
			p_imapType[i % iWidth][i / iWidth] = 1;

			pObjects[i] = (Object*)malloc(sizeof(Object));

			//Corner and horizontal wall
			*(pObjects[i]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(imapType - 2), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);
		}

		if (imapType == 13) // SPIKE
		{
			p_imapType[i % iWidth][i / iWidth] = 1;

			pObjects[i] = (Object*)malloc(sizeof(Object));

			//Corner and horizontal wall
			*(pObjects[i]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(imapType), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);
		}

		if (imapType == 2) { // BLACK
			p_imapType[i % iWidth][i / iWidth] = 1;

			pObjects[i] = (Object*)malloc(sizeof(Object));

			//Out of bound texture
			*(pObjects[i]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(0), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);
		}

		if (imapType == 44) // WAKE PLAYER
		{
			p_imapType[i % iWidth][i / iWidth] = 0;

			pObjects[i] = (Object*)malloc(sizeof(Object));

			*(pObjects[i]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(2), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			pPlayer[iPlayerCounter] = (Player*)malloc(sizeof(Player));

			//Player
			*(pPlayer[iPlayerCounter]) = Player(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(12), pCamera,
				ResourceManager::GetInstance()->GetShaderById(1), position, rotation, scale, 6, 1, 0, 0.1, true);

			iMainPlayer = iPlayerCounter;

			iPlayerCounter++;
		}

		if (imapType == 85) // TORCH
		{
			p_imapType[i % iWidth][i / iWidth] = 1;

			pObjects[i] = (Object*)malloc(sizeof(Object));

			*(pObjects[i]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(2), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			pObstacles[iObstacleCounter] = (Animation*)malloc(sizeof(Animation));

			*(pObstacles[iObstacleCounter]) = Animation(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(90), pCamera,
				ResourceManager::GetInstance()->GetShaderById(1), position, rotation, scale, 4, 1, 0, 0.1);

			iObstacleCounter++;
		}

		if (imapType == 10) // LEFT WALL
		{
			p_imapType[i % iWidth][i / iWidth] = 2;

			pObjects[i] = (Object*)malloc(sizeof(Object));

			//Left wall
			*(pObjects[i]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(2), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			pHorizontalWall[iHorizontalWallCounter] = (Object*)malloc(sizeof(Object));

			*(pHorizontalWall[iHorizontalWallCounter]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(8), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			iHorizontalWallCounter++;
		}

		if (imapType == 11) // RIGHT WALL
		{
			p_imapType[i % iWidth][i / iWidth] = 3;

			pObjects[i] = (Object*)malloc(sizeof(Object));

			//Right wall
			*(pObjects[i]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(2), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			pHorizontalWall[iHorizontalWallCounter] = (Object*)malloc(sizeof(Object));

			*(pHorizontalWall[iHorizontalWallCounter]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(9), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			iHorizontalWallCounter++;
		}

		if (imapType == 12) // sleep player
		{
			//A sleep player is marked as an obstacle (for enemy movement)
			p_imapType[i % iWidth][i / iWidth] = 1;

			pObjects[i] = (Object*)malloc(sizeof(Object));

			*(pObjects[i]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(2), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			pPlayer[iPlayerCounter] = (Player*)malloc(sizeof(Player));

			//"Sleep" player
			*(pPlayer[iPlayerCounter]) = Player(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(14), pCamera,
				ResourceManager::GetInstance()->GetShaderById(1), position, rotation, scale, 6, 1, 0, 0.1, false); // Sleep texture here

			iPlayerCounter++;
		}

		if (imapType == 14) // SMALL CORNER
		{
			p_imapType[i % iWidth][i / iWidth] = 3;

			pObjects[i] = (Object*)malloc(sizeof(Object));

			*(pObjects[i]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(2), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			pHorizontalWall[iHorizontalWallCounter] = (Object*)malloc(sizeof(Object));

			*(pHorizontalWall[iHorizontalWallCounter]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(92), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			iHorizontalWallCounter++;
		}

		if (imapType == 15) // SMALL CORNER
		{
			p_imapType[i % iWidth][i / iWidth] = 2;

			pObjects[i] = (Object*)malloc(sizeof(Object));

			*(pObjects[i]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(2), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			pHorizontalWall[iHorizontalWallCounter] = (Object*)malloc(sizeof(Object));

			*(pHorizontalWall[iHorizontalWallCounter]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(93), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			iHorizontalWallCounter++;
		}

		if (imapType == 16) // SMALL CORNER
		{
			p_imapType[i % iWidth][i / iWidth] = 3;

			pObjects[i] = (Object*)malloc(sizeof(Object));

			*(pObjects[i]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(2), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			pHorizontalWall[iHorizontalWallCounter] = (Object*)malloc(sizeof(Object));

			*(pHorizontalWall[iHorizontalWallCounter]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(94), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			iHorizontalWallCounter++;
		}

		if (imapType == 17) // SMALL CORNER
		{
			p_imapType[i % iWidth][i / iWidth] = 2;

			pObjects[i] = (Object*)malloc(sizeof(Object));

			*(pObjects[i]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(2), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			pHorizontalWall[iHorizontalWallCounter] = (Object*)malloc(sizeof(Object));

			*(pHorizontalWall[iHorizontalWallCounter]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(95), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			iHorizontalWallCounter++;
		}

		if (imapType == 20) // Left wall with obsticle
		{
			p_imapType[i % iWidth][i / iWidth] = 1;

			pObjects[i] = (Object*)malloc(sizeof(Object));

			*(pObjects[i]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(13), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			pHorizontalWall[iHorizontalWallCounter] = (Object*)malloc(sizeof(Object));

			*(pHorizontalWall[iHorizontalWallCounter]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(8), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			iHorizontalWallCounter++;

		}

		if (imapType == 21) // Right wall with obsticle
		{
			p_imapType[i % iWidth][i / iWidth] = 1;

			pObjects[i] = (Object*)malloc(sizeof(Object));

			*(pObjects[i]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(13), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			pHorizontalWall[iHorizontalWallCounter] = (Object*)malloc(sizeof(Object));

			*(pHorizontalWall[iHorizontalWallCounter]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(9), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			iHorizontalWallCounter++;

		}

		if (imapType == 22) // Target
		{
			p_imapType[i % iWidth][i / iWidth] = 0;

			pTargetPosition[iTargetCounter] = position;
			iTargetCounter++;

			pObjects[i] = (Object*)malloc(sizeof(Object));

			//Target
			*(pObjects[i]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(27), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);
		}

		if (imapType == 23) // Spawn
		{
			p_imapType[i % iWidth][i / iWidth] = 0;

			pSpawnPosition[iSpawnCounter] = position;
			iSpawnCounter++;

			pObjects[i] = (Object*)malloc(sizeof(Object));

			//Spawn
			*(pObjects[i]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(28), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);
		}

		if (imapType == 24) // Player + spawn
		{
			p_imapType[i % iWidth][i / iWidth] = 0;
			pTargetPosition[iTargetCounter] = position;
			iTargetCounter++;

			pObjects[i] = (Object*)malloc(sizeof(Object));

			*(pObjects[i]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(27), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			pPlayer[iPlayerCounter] = (Player*)malloc(sizeof(Player));

			*(pPlayer[iPlayerCounter]) = Player(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(12), pCamera,
				ResourceManager::GetInstance()->GetShaderById(1), position, rotation, scale, 6, 1, 0, 0.1, true);

			iMainPlayer = iPlayerCounter;

			iPlayerCounter++;
		}

		if (imapType == 45) // Enemy
		{
			p_imapType[i % iWidth][i / iWidth] = 0;

			pObjects[i] = (Object*)malloc(sizeof(Object));

			*(pObjects[i]) = Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(2), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			pEnemy[iEnemyCounter] = (Enemy*)malloc(sizeof(Enemy));

			//Enemy
			*(pEnemy[iEnemyCounter]) = Enemy(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(107), pCamera,
				ResourceManager::GetInstance()->GetShaderById(1), position, rotation, scale, 6, 1, 0, 0.1, true, Vector3(0.0f, 0.0f, 0.0f)); // Sleep texture here

			iEnemyCounter++;
		}
	}

	//Set the targeting position of all enemies according to the main player
	for (int i = 0; i < iNumEnemy; i++) {
		pEnemy[i]->SetPlayerLockPosition(pPlayer[iMainPlayer]->GetPosition());
	}

	iNumOfMoves = 0;

	//Get move limit for each star
	iStar = new int[3];
	fscanf(filePointer, "Star: %d %d %d\n", &iStar[0], &iStar[1], &iStar[2]);

	fclose(filePointer);
}

void SceneManager::Update(float deltaTime)
{
	//Set players and enemies movement abitity
	SetPlayerMovement();
	SetEnemyMovement();
	SetEnemyPlayerBehavior();

	//Active players move
	for (int i = 0; i < iNumPlayer; i++) 
	{
		pPlayer[i]->Move(deltaTime);
		pPlayer[i]->Update(deltaTime);
	}

	//Enemies move
	for (int i = 0; i < iNumEnemy; i++)
	{
		pEnemy[i]->Move(deltaTime);
		pEnemy[i]->Update(deltaTime);
	}

	//Animation
	for (int i = 0; i < iNumObstacle; i++)
	{
		pObstacles[i]->Update(deltaTime);
	}

	//Move camera according to player if needed
	pCamera->Move(deltaTime);

	//Spawn player if step into spawn square
	if (isSpawnActive) {
		SpawnPlayer();
	}

	//Active nearby players
	ActivatePlayer();

	//Check if the game has ended
	if (!hasEnded) {
		CheckWinCondition();
	}
}

void SceneManager::Key(unsigned char keyPressed)
{
	//Player movement
	if (!hasEnded) 
	{
		//Check if at least one player has moved
		bool* hasMoved = new bool;
		*hasMoved = false;

		//Call Key function of each player
		for (int i = 0; i < iNumPlayer; i++) {
			pPlayer[i]->Key(keyPressed, hasMoved);
		}

		//Camera input -> movement
		//Number of square in a row on screen: row = Globals::screenWidth / SQUARE_SIZE, number of square in a column on screen: column = Globals::screenWidth / SQUARE_SIZE
		cameraFixPosition = pPlayer[iMainPlayer]->GetCoordinate();

		//Fix main player in the middle of the screen with row / 2 and column / 2
		//Only move camera if at least one player move
		if(*hasMoved)
		{
			if ((keyPressed & (1 << 0)) && (cameraFixPosition.x > (Globals::screenWidth / SQUARE_SIZE) * 0.5f) && (iWidth - cameraFixPosition.x > (Globals::screenWidth / SQUARE_SIZE) * 0.5f - 1.0f))
			{
				pCamera->Inputs(keyPressed);
			}
			if ((keyPressed & (1 << 1)) && (cameraFixPosition.y > (Globals::screenHeight / SQUARE_SIZE) * 0.5f) && (iHeight - cameraFixPosition.y > (Globals::screenHeight / SQUARE_SIZE) * 0.5f - 1.0f))
			{
				pCamera->Inputs(keyPressed);
			}
			if ((keyPressed & (1 << 2)) && (cameraFixPosition.x >= (Globals::screenWidth / SQUARE_SIZE) * 0.5f) && (iWidth - cameraFixPosition.x > (Globals::screenWidth / SQUARE_SIZE) * 0.5f))
			{
				pCamera->Inputs(keyPressed);
			}
			if ((keyPressed & (1 << 3)) && (cameraFixPosition.y >= (Globals::screenHeight / SQUARE_SIZE) * 0.5f) && (iHeight - cameraFixPosition.y > (Globals::screenHeight / SQUARE_SIZE) * 0.5f))
			{
				pCamera->Inputs(keyPressed);
			}

			//Update the targeting position of all enemies according to the main player
			for (int i = 0; i < iNumEnemy; i++)
			{
				pEnemy[i]->SetPlayerLockPosition(pPlayer[iMainPlayer]->GetPosition());
				pEnemy[i]->Key(keyPressed);
			}
		}

		//Update score if at least one active player has moved
		if (*hasMoved) 
		{
			iNumOfMoves++;
			iNumOfMoves = iNumOfMoves < 999 ? iNumOfMoves : 999;
		}

		delete hasMoved;
	}
}

//Set player movement ability(left, right, up, down)
void SceneManager::SetPlayerMovement()
{
	for (int i = 0; i < iNumPlayer; i++)
	{
		//Enable all movement ability before checking
		pPlayer[i]->SetMoveRightStatus(true);
		pPlayer[i]->SetMoveLeftStatus(true);
		pPlayer[i]->SetMoveDownStatus(true);
		pPlayer[i]->SetMoveUpStatus(true);

		if (pPlayer[i]->GetActiveStatus())
		{
			Vector3 coordinate = pPlayer[i]->GetCoordinate();

			//Check surrounding map after each move
			//If the right of player is an obstacle (or left wall), or player is on right wall, the player cannot move right
			if ((p_imapType[(int)std::round(coordinate.x)][(int)std::round(coordinate.y)] == 3))
			{
				pPlayer[i]->SetMoveRightStatus(false);
			}
			else if (p_imapType[(int)std::round(coordinate.x) + 1][(int)std::round(coordinate.y)] == 1 || p_imapType[(int)std::round(coordinate.x) + 1][(int)std::round(coordinate.y)] == 2)
			{
				pPlayer[i]->SetMoveRightStatus(false);
			}

			//If the left of player is an obstacle (or right wall), or player is on left wall, the player cannot move left
			if ((p_imapType[(int)std::round(coordinate.x)][(int)std::round(coordinate.y)] == 2))
			{
				pPlayer[i]->SetMoveLeftStatus(false);
			}
			else if (p_imapType[(int)std::round(coordinate.x) - 1][(int)std::round(coordinate.y)] == 1 || p_imapType[(int)std::round(coordinate.x) - 1][(int)std::round(coordinate.y)] == 3)
			{
				pPlayer[i]->SetMoveLeftStatus(false);
			}

			//If the bottom of player is an obstacle, the player cannot move down
			if (p_imapType[(int)std::round(coordinate.x)][(int)std::round(coordinate.y) + 1] == 1)
			{
				pPlayer[i]->SetMoveDownStatus(false);
			}

			//If the top of player is an obstacle, the player cannot move down
			if (p_imapType[(int)std::round(coordinate.x)][(int)std::round(coordinate.y) - 1] == 1)
			{
				pPlayer[i]->SetMoveUpStatus(false);
			}
		}
	}
}

void SceneManager::SetEnemyMovement()
{
	for (int i = 0; i < iNumEnemy; i++)
	{
		//Enable all movement ability before checking
		pEnemy[i]->SetMoveRightStatus(true);
		pEnemy[i]->SetMoveLeftStatus(true);
		pEnemy[i]->SetMoveDownStatus(true);
		pEnemy[i]->SetMoveUpStatus(true);

		if (pEnemy[i]->GetActiveStatus())
		{
			Vector3 coordinate = pEnemy[i]->GetCoordinate();

			//Check surrounding map after each move
			//If the right of enemy is an obstacle (or left wall), or enemy is on right wall, the enemy cannot move right
			if ((p_imapType[(int)std::round(coordinate.x)][(int)std::round(coordinate.y)] == 3))
			{
				pEnemy[i]->SetMoveRightStatus(false);
			}
			else if (p_imapType[(int)std::round(coordinate.x) + 1][(int)std::round(coordinate.y)] == 1 || p_imapType[(int)std::round(coordinate.x) + 1][(int)std::round(coordinate.y)] == 2)
			{
				pEnemy[i]->SetMoveRightStatus(false);
			}

			//If the left of enemy is an obstacle (or right wall), or enemy is on left wall, the enemy cannot move left
			if ((p_imapType[(int)std::round(coordinate.x)][(int)std::round(coordinate.y)] == 2))
			{
				pEnemy[i]->SetMoveLeftStatus(false);
			}
			else if (p_imapType[(int)std::round(coordinate.x) - 1][(int)std::round(coordinate.y)] == 1 || p_imapType[(int)std::round(coordinate.x) - 1][(int)std::round(coordinate.y)] == 3)
			{
				pEnemy[i]->SetMoveLeftStatus(false);
			}

			//If the bottom of enemy is an obstacle, the enemy cannot move down
			if (p_imapType[(int)std::round(coordinate.x)][(int)std::round(coordinate.y) + 1] == 1)
			{
				pEnemy[i]->SetMoveDownStatus(false);
			}

			//If the top of enemy is an obstacle, the enemy cannot move down
			if (p_imapType[(int)std::round(coordinate.x)][(int)std::round(coordinate.y) - 1] == 1)
			{
				pEnemy[i]->SetMoveUpStatus(false);
			}
		}
	}
}

void SceneManager::SetEnemyPlayerBehavior()
{
	for (int i = 0; i < iNumPlayer; i++)
	{
		if (pPlayer[i]->GetActiveStatus())
		{
			for (int j = 0; j < iNumEnemy; j++) 
			{
				//Get position of enemy in player perspective (means vector player->enemy)
				Vector3 nearEnemyCoordinate;
				nearEnemyCoordinate.x = (int)std::round(pEnemy[j]->GetCoordinate().x) - (int)std::round(pPlayer[i]->GetCoordinate().x);
				nearEnemyCoordinate.y = (int)std::round(pEnemy[j]->GetCoordinate().y) - (int)std::round(pPlayer[i]->GetCoordinate().y);

				//Disable player movement ability based on position of nearby enemy
				if ((int)std::floor(nearEnemyCoordinate.x) == 1 && (int)std::floor(nearEnemyCoordinate.y) == 0)
				{
					pPlayer[i]->SetMoveRightStatus(false);
				}
				else if ((int)std::floor(nearEnemyCoordinate.x) == -1 && (int)std::floor(nearEnemyCoordinate.y) == 0)
				{
					pPlayer[i]->SetMoveLeftStatus(false);
				}
				else if ((int)std::floor(nearEnemyCoordinate.y) == 1 && (int)std::floor(nearEnemyCoordinate.x) == 0)
				{
					pPlayer[i]->SetMoveDownStatus(false);
				}
				else if ((int)std::floor(nearEnemyCoordinate.y) == -1 && (int)std::floor(nearEnemyCoordinate.x) == 0)
				{
					pPlayer[i]->SetMoveUpStatus(false);
				}

				//Disable enemy movement ability based on position of nearby player, so the enemy doesn't crash into player
				if ((int)std::floor(nearEnemyCoordinate.x) == 1 && std::fabs(nearEnemyCoordinate.y) <= 1.0f)
				{
					pEnemy[j]->SetMoveLeftStatus(false);
				}
				if ((int)std::floor(nearEnemyCoordinate.x) == -1 && std::fabs(nearEnemyCoordinate.y) <= 1.0f)
				{
					pEnemy[j]->SetMoveRightStatus(false);
				}
				if ((int)std::floor(nearEnemyCoordinate.y) == -1 && std::fabs(nearEnemyCoordinate.x) <= 1.0f)
				{
					pEnemy[j]->SetMoveDownStatus(false);
				}
				if ((int)std::floor(nearEnemyCoordinate.y) == 1 && std::fabs(nearEnemyCoordinate.x) <= 1.0f)
				{
					pEnemy[j]->SetMoveUpStatus(false);
				}
			}
		}
	}
}

//Spawn new players in all spawn square
void SceneManager::SpawnPlayer()
{
	for (int i = 0; i < iNumSpawn && isSpawnActive; i++)
	{
		for (int j = 0; j < iNumPlayer && isSpawnActive; j++)
		{
			if (pPlayer[j]->GetActiveStatus() && pPlayer[j]->CheckPosition(pSpawnPosition[i]))
			{
				//Check if any active player step into spawn square
				Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f);
				Vector3 scale = Vector3(SQUARE_SIZE, SQUARE_SIZE, 1.0f);

				for (int k = 0; k < iNumSpawn; k++)
				{
					pPlayer[iNumPlayer + k] = (Player*)malloc(sizeof(Player));

					*(pPlayer[iNumPlayer + k]) = Player(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(12), pCamera,
						ResourceManager::GetInstance()->GetShaderById(1), pSpawnPosition[k], rotation, scale, 6, 1, 0, 0.1, true);
				}

				iNumPlayer += iNumSpawn;

				pPlayer[j]->SetDrawnStatus(false);

				//Play spawn audio
				AudioManager::GetInstance()->GetAudioById(4)->PlayMusic();

				//Disable spawn square
				for (int k = 0; k < iWidth * iHeight; k++)
				{
					for (int l = 0; l < iNumSpawn; l++)
					{
						if (pObjects[k]->CheckPosition(pSpawnPosition[l]))
						{
							pObjects[k]->SetTexture(ResourceManager::GetInstance()->GetTextureById(29));
						}
					}
				}

				isSpawnActive = false;
			}
		}
	}
}

//Check nearby inactive player, activate them
void SceneManager::ActivatePlayer()
{
	for (int i = 0; i < iNumPlayer; i++)
	{
		if (pPlayer[i]->GetActiveStatus())
		{
			for (int j = 0; j < iNumPlayer; j++)
			{
				//If player j is close to player i and player j is asleep
				if (pPlayer[i]->CheckCloseObject(*pPlayer[j]) && !pPlayer[j]->GetActiveStatus())
				{
					pPlayer[j]->SetActiveStatus(true);
					pPlayer[j]->SetTexture(*pPlayer[i]); // When wake up

					//When a player wake up, that position is no longer marked as obstacle
					p_imapType[(int)std::round(pPlayer[j]->GetCoordinate().x)][(int)std::round(pPlayer[j]->GetCoordinate().y)] = 0;
				}
			}
		}
	}
}

//If all active players are in target square and all target square has at least one active player, end the game
void SceneManager::CheckWinCondition()
{
	int iNumberTargetReached = 0, iNumberActivePlayerReached = 0, iNumberActivePlayer = 0;

	//Check if all target square has at least one active player
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

	// Check if all active players are in target square
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

	//If ending criteria are satisfied, stop the game, play ending music and write the resut to file
	if (iNumberTargetReached == iNumTarget && iNumberActivePlayer == iNumberActivePlayerReached)
	{
		hasEnded = true;
		AudioManager::GetInstance()->GetAudioById(6)->SetVolume(0);
		AudioManager::GetInstance()->GetAudioById(5)->PlayMusic();
		WriteResult();
	}
}

int SceneManager::GetNumberOfMoves()
{
	return iNumOfMoves;
}

int* SceneManager::GetStarIndex()
{
	return iStar;
}

bool SceneManager::GetEndedStatus()
{
	return hasEnded;
}

int SceneManager::GetNumberOfStar()
{
	for (int i = 0; i < 3; i++) 
	{
		if (iNumOfMoves > iStar[i]) 
		{
			return i;
		}
	}

	return 3;
}

//Write the number of star of current level into a file
void SceneManager::WriteResult()
{
	int* pointOfLevel = new int[NUM_OF_LEVELS + 1];

	//Read point of every level and store into an array
	FILE* readPoiter;

	try
	{
		readPoiter = fopen("../Resources/Level/Level.txt", "r");
	}
	catch (...)
	{
		printf("Cannot open score file");
	}

	for (int i = 1; i <= NUM_OF_LEVELS; i++) {
		fscanf(readPoiter, "%d\n", &pointOfLevel[i]);
	}

	fclose(readPoiter);

	//Overwrite the score of the current level if the score is higher than the score from the file
	int star = GetNumberOfStar();
	pointOfLevel[iLevelNumber] = pointOfLevel[iLevelNumber] > star ? pointOfLevel[iLevelNumber] : star;

	//Rewrite the file storing all the score after checking high score of current level
	FILE* writePoiter;

	try
	{
		writePoiter = fopen("../Resources/Level/Level.txt", "w");
	}
	catch (...)
	{
		printf("Cannot open score file");
	}

	for (int i = 1; i <= NUM_OF_LEVELS; i++) {
		fprintf(writePoiter, "%d\n", pointOfLevel[i]);
	}

	fclose(writePoiter);

	delete pointOfLevel;
}

//Draw floor -> players & enemies -> obsticle -> vertical walls
void SceneManager::Draw()
{
	for (int i = 0; i < iWidth * iHeight; i++)
	{
		pObjects[i]->Draw();
	}

	for (int i = 0; i < iNumPlayer; i++) 
	{
		if (pPlayer[i]->GetDrawnStatus()) 
		{
			pPlayer[i]->Draw();
		}
	}

	for (int i = 0; i < iNumEnemy; i++)
	{
		pEnemy[i]->Draw();
	}

	for (int i = 0; i < iNumObstacle; i++)
	{
		pObstacles[i]->Draw();
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
		free(pObjects[i]);
	}
	free(pObjects);

	for (int i = 0; i < iWidth; i++)
	{
		free(p_imapType[i]);
	}
	free(p_imapType);

	for (int i = 0; i < iNumHorizontalWall; i++)
	{
		free(pHorizontalWall[i]);
	}
	free(pHorizontalWall);
	
	for (int i = 0; i < iNumPlayer; i++) 
	{
		free(pPlayer[i]);
	}
	free(pPlayer);

	for (int i = 0; i < iNumEnemy; i++)
	{
		free(pEnemy[i]);
	}
	free(pEnemy);

	for (int i = 0; i < iNumObstacle; i++)
	{
		free(pObstacles[i]);
	}
	free(pObstacles);
	
	free(pTargetPosition);
	free(pSpawnPosition);

	delete iStar;
	delete pCamera;
}