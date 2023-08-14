#pragma once
#include "../Utilities/utilities.h"

class Singleton
{
protected:
	Singleton() {}
	~Singleton() {}
	/*implicit methods exist for the copy constructor and operator= and we want to forbid calling them.*/
	Singleton(const Singleton&) {}
	Singleton& operator =(const Singleton&) {}

public:
	static void CreateInstance()
	{
		if (ms_pInstance == NULL)
			ms_pInstance = new Singleton;
	}
	static Singleton* GetInstance()
	{
		return ms_pInstance;
	}
	static void DestroyInstance()
	{
		if (ms_pInstance)
		{
			delete ms_pInstance;
			ms_pInstance = NULL;
		}
	}

protected:
	static Singleton* ms_pInstance;
};