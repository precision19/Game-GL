#pragma once
#include "PrefabManager.h"
#include <map>
#include <stack>
#include "GameObject.h"
#include "Player.h"
#include "TreasureChest.h"
#include "Block.h"
#include "Star.h"
#include "Bullet.h"
#include "Gun.h"
#include "Guard.h"
#include "SawBlade.h"
#include "Chaser.h"
#include "SpinnerFly.h"

class ObjectPool
{
protected:
	static ObjectPool* ms_Instance;
	map<string, stack<GameObject*>> m_Pool;
public:
	static void CreateInstance();
	static ObjectPool* GetInstance();
	static void DestroyInstance();

	ObjectPool();
	GameObject* GetPooledObject(string);
	void ReturnObject(GameObject*);
	~ObjectPool();
};

