#include "stdafx.h"
#include "PlayerPrefs.h"

PlayerPrefs* PlayerPrefs::ms_Instance = NULL;

void PlayerPrefs::CreateInstance()
{
	if (ms_Instance == NULL)
		ms_Instance - new PlayerPrefs();
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
}

void PlayerPrefs::GetData(int levelId)
{

}

void PlayerPrefs::SetData(int levelId, int score)
{

}

void PlayerPrefs::SaveData()
{
}

PlayerPrefs::~PlayerPrefs()
{
}
