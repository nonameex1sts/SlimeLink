#pragma once
#include "Camera.h"
#include "Object.h"
#include "../Utilities/utilities.h"
#include "Math.h"

class SceneManager {
private:
	static SceneManager* m_pInstance;
	Camera* camera;
	Object** objects;
	int numObjects;
	SceneManager();
	~SceneManager();

public:
	static void CreateInstance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new SceneManager;
	};

	static SceneManager* GetInstance()
	{
		return m_pInstance;
	};

	static void DestroyInstance()
	{
		if (m_pInstance != nullptr)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	};

	void Update(ESContext* esContext, float deltaTime, unsigned char keyPressed);
	void Draw();
};

