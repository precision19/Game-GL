#pragma once
#include "StateManager.h"
#include "Button.h"
#include "LevelButton.h"
#include "Animation2D.h"
#include "AudioManager.h"
#include "PlayerPrefs.h"

class MapState : public StateBase 
{
protected: 
	StateManager* m_StateManager;
	vector<Object*> m_Objects;
	vector<LevelButton*> m_LevelButtons;
public:
	MapState();
	void SetStateManager(StateManager*);
	void OnStart();
	void Update(float deltaTime);
	void Draw();
	~MapState();
};