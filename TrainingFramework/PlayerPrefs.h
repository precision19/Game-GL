#pragma once
#include <vector>

class PlayerPrefs
{
protected:
	

	static PlayerPrefs* ms_Instance;
public:
	static void CreateInstance();
	static PlayerPrefs* GetInstance();
	static void DestroyInstance();

	PlayerPrefs();

	void SetData(int, int);
};

