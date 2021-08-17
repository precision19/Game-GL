#pragma once
#include "StateManager.h"
#include "Button.h"
#include "Dungeon.h"
#include "Trap.h"
#include "GameObject.h"
#include "Block.h"
#include "Player.h"
#include "Bullet.h"
#include "Gun.h"

class LevelState : public StateBase 
{
protected:

	Bullet* m_bullet;
	int m_i;
	float m_Time;

	vector<GameObject*> m_BulletObjects;
	vector<Object*> m_Decorations;
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
	void Draw();
	void Update(float);
	~LevelState();
};