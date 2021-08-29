#include "stdafx.h"
#include "SceneManager.h"
#include <iostream>

SceneManager* SceneManager::ms_Instance = NULL;

void SceneManager::CreateInstance()
{
	if (ms_Instance == NULL)
		ms_Instance = new SceneManager();
}

SceneManager* SceneManager::GetInstance()
{
	return ms_Instance;
}

void SceneManager::DestroyInstance()
{
	if (ms_Instance)
	{
		delete ms_Instance;
		ms_Instance = NULL;
	}
}

SceneManager::SceneManager() 
{ 
	
	MenuState* menuState = new MenuState();
	menuState->SetStateManager(this);
	AddState(menuState);

	MapState* mapState = new MapState();
	mapState->SetStateManager(this);
	AddState(mapState);

	m_LevelState = new LevelState();
	m_LevelState->SetStateManager(this);
	AddState(m_LevelState);

}

void SceneManager::Draw()
{
	m_CurrentState->Draw();
}

void SceneManager::Update(float deltaTime)
{
	if (Input::CheckButtonBuffer(BUTTON_QUIT))
	{
		// Tat game
	}

	m_CurrentState->Update(deltaTime);
	
	for (int i = 0; i < 22; i++)
		if (Input::CheckButtonBuffer(i))
		{
			m_LevelState->SetLevel(i);
			SwitchState("Level");
			return;
		}
}


StateBase* SceneManager::getCurrentState() 
{
	return m_CurrentState;
}
