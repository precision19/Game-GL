#pragma once
#include "StateManager.h"

class MapState : public StateBase 
{
protected: 
	StateManager* m_StateManager;
public:
	MapState();
	void SetStateManager(StateManager*);
	void OnStart();
	void Update(float deltaTime);
	void Draw();
};