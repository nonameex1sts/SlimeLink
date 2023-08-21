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
	int** p_imapType;;
	Player* player;

	int iWidth;
	int iHeight;

	Vector3 star;
	
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

	void Update(float deltaTime, unsigned char keyPressed);
	void Draw();
};

