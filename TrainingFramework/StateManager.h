#pragma once
#include "StateBase.h"
#include "MenuState.h"
#include "LevelState.h"

class StateManager {
public:
	StateBase* state;
	StateManager();
	void Update(float deltaTime);
	void Draw();
	void Destroy();
};