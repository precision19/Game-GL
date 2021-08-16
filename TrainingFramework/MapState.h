#pragma once
#include "StateManager.h"
#include "Button.h"
#include "Animation2D.h"

class MapState : public StateBase 
{
protected: 
	StateManager* m_StateManager;
	vector<Object*> m_Objects;
public:
	MapState();
	void SetStateManager(StateManager*);
	void OnStart();
	void Update(float deltaTime);
	void Draw();
	~MapState();
};