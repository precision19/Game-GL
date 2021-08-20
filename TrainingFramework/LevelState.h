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

class LevelState : public StateBase 
{
protected:
	StateManager* m_StateManager;

	Player* m_Player;
	Object* m_Gate;
	TreasureChest* m_Chest;
	Star* m_StarPrefab;
	Block* m_BlockPrefab;
	SawBlade* m_SawPrefab;
	Guard* m_GuardPrefab;
	Bullet* m_BulletPrefab;
	Gun* m_GunPrefab;
	Chaser* m_Chaser;
	SpinnerFly* m_SpinnerPrefab;
	int m_i;
	float m_Time;
	int m_LevelID;

	vector<Object*> m_GameObjects;
	vector<Object*> m_PauseMenu;
public:
	LevelState();
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