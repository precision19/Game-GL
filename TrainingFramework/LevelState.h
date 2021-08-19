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
#include "Guard.h"
#include "Star.h"
#include "SawBlade.h"
#include "TreasureChest.h"
#include "AudioManager.h"
#include "Chaser.h"

class LevelState : public StateBase 
{
protected:
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
	int m_i;
	float m_Time;

	vector<GameObject*> m_BulletObjects;
	vector<Object*> m_Decorations;
	StateManager* m_StateManager;
	vector<Object*> m_GameObjects;
	vector<Object*> m_PauseMenu;
public:
	LevelState();
	void SetStateManager(StateManager*);
	void OnStart();
	void Restart();
	void Draw();
	void Update(float);
	~LevelState();
};