#pragma once
#include "StateBase.h"
#include <vector>

class StateManager 
{
protected:
	StateBase* m_CurrentState;
	vector<StateBase*> m_States;
public:
	StateManager();
	void AddState(StateBase*);
	virtual void Update(float deltaTime);
	virtual void Draw();
	void SwitchState(int);
	void SwitchState(string);
	virtual ~StateManager();
};