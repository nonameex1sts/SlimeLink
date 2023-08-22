#pragma once
#include "Camera.h"
#include "Object.h"
#include "Player.h"
#include "../Utilities/utilities.h"
#include "Math.h"

class SceneManager {
private:
	static SceneManager* ms_pInstance;

	Camera* pCamera;
	Object** pObjects;
	Object** pHorizontalWall;
	int** p_imapType;;
	Player** pPlayer;

	int iNumPlayer;
	int iNumHorizontalWall;
	int iWidth;
	int iHeight;

	Vector3 star;

	bool canMoveLeft = true;
	bool canMoveRight = true;
	bool canMoveUp = true;
	bool canMoveDown = true;
	
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
	void Draw();
};

