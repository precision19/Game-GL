#pragma once
#include <vector>
#include <string>

using namespace std;

class PlayerPrefs
{
protected:
	struct mapData {
		int levelID;
		int stars;
	};
	static PlayerPrefs* ms_Instance;
	vector<mapData> m_MapData;
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

