#pragma once
#include "Picture.h"
#include "Camera.h"

class Transition
{
private:
	float fTransitionTime = 20.0f;

	int status; // -1 for close, 0 for idle, 1 for open
	Picture* blocks;
	static Transition* ms_pInstance;
	Camera* pCamera;
	Transition();
	~Transition();
public:
	static void CreateInstance()
	{
		if (ms_pInstance == nullptr)
			ms_pInstance = new Transition();
	};

	static Transition* GetInstance()
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
	void Draw();
	void Update();
	void Closing();
	void Opening();
	void SetStatus(int status);
	int GetStatus();
};