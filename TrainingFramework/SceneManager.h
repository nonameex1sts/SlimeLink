#pragma once
#include "Camera.h"
#include "Object.h"
#include "../Utilities/utilities.h"
#include "Math.h"

class SceneManager {
private:
	static SceneManager* ms_pInstance;
	Camera* pCamera;
	Object** pObjects;
	int inumObjects;
	SceneManager();
	~SceneManager();

public:
	static void CreateInstance()
	{
		if (ms_pInstance == nullptr)
			ms_pInstance = new SceneManager;
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

