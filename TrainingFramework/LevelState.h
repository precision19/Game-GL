#pragma once
#include "StateManager.h"
#include "Button.h"
#include "Dungeon.h"
#include "GameObject.h"
#include "Block.h"
#include "Player.h"
#include "Bullet.h"
#include "Gun.h"
#include "Guard.h"
#include "Star.h"
#include "SawBlade.h"
#include "TreasureChest.h"
#include "SpinnerFly.h"
#include "AudioManager.h"
#include "Chaser.h"
#include "ObjectPool.h"
#include "PlayerPrefs.h"

class LevelState : public StateBase 
{
protected:
	int m_LevelID;
	int m_Score;
	int m_ScoreEnd;

	StateManager* m_StateManager;

	Player* m_Player;
	GameObject* m_Gate;
	TreasureChest* m_Chest;

	Object* m_TapToStartText;
	vector<Object*> m_Backgrounds;
	vector<GameObject*> m_GameObjects;
	vector<Object*> m_PauseMenu;
	vector<Object*> m_WinMenu;
public:
	LevelState();
	int GetLevel();
	void SetStateManager(StateManager*);
	void SetLevel(int);
	void OnStart();
	void LoadLevel();
	void Restart();
	void Draw();
	void Update(float);
	void ClearLevel();
	~LevelState();
};