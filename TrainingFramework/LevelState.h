#pragma once
#include "StateManager.h"
#include "Button.h"
#include "Dungeon.h"

class LevelState : public StateBase 
{
protected:
	StateManager* m_StateManager;
	vector<Object*> m_GameObjects;
	Button* m_PauseButton;
	Button* m_StartButton;
	vector<Object*> m_PauseMenu;
	Button* m_ReturnMapButton;
	Button* m_RestartButton;
	Button* m_SoundButton;

public:
	LevelState();
	void SetStateManager(StateManager*);
	void OnStart();
	void CreateDungeon(Object*);
	void Draw();
	void Update(float);
	~LevelState();
};