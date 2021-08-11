#pragma once
#include "SceneManager.h"
#include "PrefabManager.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Input.h"
#include "StateManager.h"

class StateBase {
public:
	StateManager* stateManager;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
	virtual void Destroy() = 0;
};