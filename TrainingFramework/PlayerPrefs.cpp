#include "stdafx.h"
#include "PlayerPrefs.h"
#include <iostream>

PlayerPrefs* PlayerPrefs::ms_Instance = NULL;

void PlayerPrefs::CreateInstance()
{
	if (ms_Instance == NULL)
		ms_Instance = new PlayerPrefs();
}

PlayerPrefs* PlayerPrefs::GetInstance()
{
	return ms_Instance;
}

void PlayerPrefs::DestroyInstance()
{
	if (ms_Instance)
	{
		delete ms_Instance;
		ms_Instance = NULL;
	}
}

PlayerPrefs::PlayerPrefs()
{
}

void PlayerPrefs::LoadData()
{
	string path = "Managers/PlayerPref.txt";
	FILE* f = fopen(path.c_str(), "r+");

	if (f == NULL)
	{
		printf("Invalid file %s\n", path.c_str());
		exit(1);
	}
	int numberOfLevel;
	fscanf(f, "#NumberOfLevel: %d\n", &numberOfLevel);
	mapData tmp;
	for (int i = 0; i < numberOfLevel; i++) {
		char keyword[20], name[20];
		int levelID, stars;
		fscanf(f, "LevelID: %d\n", &levelID);
		tmp.levelID = levelID;
		fscanf(f, "Star: %d\n", &stars);
		tmp.stars = stars;
		m_MapData.push_back(tmp);
	}
	fclose(f);
	for (int i = 0; i < m_MapData.size(); i++) {
		cout << "Level " << m_MapData[i].levelID << " has " << m_MapData[i].stars << endl;
	}
}


void PlayerPrefs::GetData(int levelId)
{

}

void PlayerPrefs::SetData(int levelID, int stars)
{
	m_MapData[levelID - 1].levelID = levelID;
	m_MapData[levelID - 1].stars = stars;
	cout << "Level " << m_MapData[levelID - 1].levelID << " has " << m_MapData[levelID - 1].stars << endl;
}

void PlayerPrefs::SaveData()
{
	string path = "Managers/PlayerPref.txt";
	FILE* f = fopen(path.c_str(), "w+");
	if (f == NULL)
	{
		printf("Invalid file %s\n", path.c_str());
		exit(1);
	}
	fprintf(f, "#NumberOfLevel: %d\n", m_MapData.size());
	for (int i = 0; i < m_MapData.size(); i++) {
		fprintf(f, "LevelID: %d\n", m_MapData.at(i).levelID);
		fprintf(f, "Star: %d\n", m_MapData.at(i).stars);
		fprintf(f, "\n");
	}
	fclose(f);
}

PlayerPrefs::~PlayerPrefs()
{
}

