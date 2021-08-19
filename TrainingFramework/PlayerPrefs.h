#pragma once
#include <vector>

using namespace std;

class PlayerPrefs
{
protected:
	static PlayerPrefs* ms_Instance;
	vector<int> m_MapData;
public:
	static void CreateInstance();
	static PlayerPrefs* GetInstance();
	static void DestroyInstance();

	PlayerPrefs();
	void LoadData();
	void GetData(int);
	void SetData(int, int);
	void SaveData();
	~PlayerPrefs();
};

