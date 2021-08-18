#include "stdafx.h"
#include "StateManager.h"

StateManager::StateManager() 
{
	m_CurrentState = NULL;
}

void StateManager::AddState(StateBase* state)
{
	if (m_CurrentState == NULL)
	{
		m_CurrentState = state;
		state->OnStart();
	}
	m_States.push_back(state);
}

void StateManager::Update(float deltaTime) 
{
	m_CurrentState->Update(deltaTime);
}

void StateManager::Draw() 
{
	m_CurrentState->Draw();
}

void StateManager::SwitchState(int id)
{
	if (id < 0 || id > m_States.size() - 1)
	{
		printf("WARNING: Can't find state with id: %s", id);
		return;
	}
	m_CurrentState->OnTranslation();
	m_CurrentState = m_States.at(id);
	m_CurrentState->OnStart();
}

void StateManager::SwitchState(string name)
{
	for each (StateBase* state in m_States)
	{
		if (state->GetName() == name)
		{
			m_CurrentState->OnTranslation();
			m_CurrentState = state;
			m_CurrentState->OnStart();
			return;
		}
	}

	printf("WARNING: Can't find state with name: %s", name.c_str());
}

StateManager::~StateManager()
{
	for (int i = 0; i < m_States.size(); i++)
	{
		delete m_States.at(i);
	}
}
