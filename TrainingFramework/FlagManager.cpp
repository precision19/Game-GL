#include "stdafx.h"
#include "FlagManager.h"

FlagManager* FlagManager::ms_Instance = NULL;

void FlagManager::CreateInstance()
{
	if (ms_Instance == NULL)
		ms_Instance = new FlagManager();
}

FlagManager* FlagManager::GetInstance()
{
	return ms_Instance;
}

void FlagManager::DestroyInstance()
{
	if (ms_Instance)
	{
		delete ms_Instance;
		ms_Instance = NULL;
	}
}

FlagManager::FlagManager()
{
	for (int i = 0; i < m_FlagNumber; i++)
		m_Flags.push_back(0);
}

void FlagManager::Set(int flagId, int value)
{
	if (flagId < 0 || flagId > m_FlagNumber)
	{
		printf("Flag's ID is invalid");
	}
	m_Flags.at(flagId) = value;
}

bool FlagManager::Check(int flagId, int value)
{
	if (flagId < 0 || flagId > m_FlagNumber)
	{
		printf("Flag's ID is invalid");
		return false;
	}
	if (m_Flags.at(flagId) == 0)
		printf("WARNING: flag %d is not setted", flagId);
	return m_Flags.at(flagId) == value;
}

bool FlagManager::Check(int flagId, int value1, int value2)
{
	if (flagId < 0 || flagId > m_FlagNumber)
	{
		printf("Flag's ID is invalid");
		return false;
	}
	if (m_Flags.at(flagId) == 0)
		printf("WARNING: flag %d is not setted", flagId);
	return m_Flags.at(flagId) == value1 || m_Flags.at(flagId) == value2;
}
