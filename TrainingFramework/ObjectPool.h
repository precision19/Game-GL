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
#include "DynamicBlade.h"

class ObjectPool
{
protected:
	static ObjectPool* ms_Instance;
	map<string, stack<GameObject*>> m_Pool;
	map<string, stack<Object*>> m_ObjectPool;
public:
	static void CreateInstance();
	static ObjectPool* GetInstance();
	static void DestroyInstance();

	ObjectPool();
	Object* GetPooledObject(string);
	void ReturnPooledObject(Object*);
	GameObject* GetGameObject(string);
	void ReturnGameObject(GameObject*);
	~ObjectPool();
};

