#pragma once
#include "Camera.h"
#include "Object.h"
#include "Player.h"
#include "../Utilities/utilities.h"
#include "Math.h"
#include "Animation.h"

class SceneManager {
private:
	static SceneManager* ms_pInstance;

	Camera* pCamera;
	Object** pObjects;
	Object** pHorizontalWall;
	int** p_imapType;;
	Player** pPlayer;
	Vector3* pTargetPosition;
	Vector3* pSpawnPosition;

	Animation** pObstacles;

	int iNumObstacle;
	int iMainPlayer;
	int iNumPlayer;
	int iNumTarget;
	int iNumSpawn;
	int iNumHorizontalWall;
	int iWidth;
	int iHeight;

	int iNumOfMoves;
	
	Vector3 cameraFixPosition;
	Vector3 deltaCameraPosition;
	int* iStar;

	unsigned char keyPressed = 0;

	bool isCameraMove = false;
	bool hasEnded = false;
	bool isSpawnActive = true;
	
	SceneManager();
	SceneManager(int ilevelNumber);
	~SceneManager();

public:
	static void CreateInstance(int ilevelNumber)
	{
		if (ms_pInstance == nullptr)
			ms_pInstance = new SceneManager(ilevelNumber);
	};

	static SceneManager* GetInstance()
	{
		return ms_pInstance;
	};

	static void DestroyInstance()
	{
		if (ms_pInstance != nullptr)
		{
			delete ms_pInstance;
			ms_pInstance = nullptr;
		}
	};

	void Update(float deltaTime);
	void Key(unsigned char keyPressed);
	void SetPlayerMovement();
	void SpawnPlayer();
	void ActivatePlayer();
	void CheckWinCondition();
	int GetNumberOfMoves();
	int* GetStarIndex();
	bool GetEndedStatus();
	int GetNumberOfStar();
	void Draw();
};

