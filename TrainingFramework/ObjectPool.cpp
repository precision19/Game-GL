#include "stdafx.h"
#include "ObjectPool.h"

ObjectPool* ObjectPool::ms_Instance = NULL;

void ObjectPool::CreateInstance()
{
	if (ms_Instance == NULL)
		ms_Instance = new ObjectPool();
}

ObjectPool* ObjectPool::GetInstance()
{
	return ms_Instance;
}

void ObjectPool::DestroyInstance()
{
	if (ms_Instance)
	{
		delete ms_Instance;
		ms_Instance = NULL;
	}
}

ObjectPool::ObjectPool()
{
	FILE* f = fopen("Managers/ObjectPool.txt", "r+");

	if (f == NULL)
	{
		printf("Invalid file %s\n", "Managers/GameObjectPrefab.txt");
		exit(1);
	}
	char keyword[20], name[20], type[20];
	int numberOfPrefabs, number, amount;
	fscanf(f, "#PrefabObject: %d\n", &numberOfPrefabs);

	for (int i = 0; i < numberOfPrefabs; i++)
	{
		fscanf(f, "%s %s x%d\n", keyword, type, &amount);
		GameObject* prefab = NULL;
		if (strcmp(type, PLAYER) == 0)
		{
			Player* player = new Player();
			fscanf(f, "COLLIDER_SIZE %d\n", &number);
			player->SetCollider(number);
			fscanf(f, "RENDERER %s\n", name);
			player->SetRenderer(name);
			fscanf(f, "RENDERER %s\n", name);
			player->SetRenderer(name);
			fscanf(f, "RENDERER %s\n", name);
			player->SetRenderer(name);
			fscanf(f, "RENDERER %s\n", name);
			player->SetRenderer(name);
			fscanf(f, "RENDERER %s\n", name);
			player->SetRenderer(name);
			fscanf(f, "SPEED %d\n", &number);
			player->SetSpeed(number);
			fscanf(f, "JUMP_FORCE %d\n", &number);
			player->SetJumpForce(number);

			prefab = player;
		}
		else if (strcmp(type, GATE) == 0)
		{
			GameObject* gate = new GameObject(GATE);
			fscanf(f, "RENDERER %s\n", name);
			gate->SetRenderer(name);

			prefab = gate;
		}
		else if (strcmp(type, TREASURE_CHEST) == 0)
		{
			TreasureChest* treasureChest = new TreasureChest();
			fscanf(f, "COLLIDER_SIZE %d\n", &number);
			treasureChest->SetCollider(number);
			fscanf(f, "RENDERER %s\n", name);
			treasureChest->SetRenderer(name);
			fscanf(f, "RENDERER %s\n", name);
			treasureChest->SetRenderer(name);

			prefab = treasureChest;
		}
		else if (strcmp(type, BLOCK) == 0)
		{
			Block* block = new Block();
			fscanf(f, "COLLIDER_SIZE %d\n", &number);
			block->SetCollider(number);
			fscanf(f, "RENDERER %s\n", name);
			block->SetRenderer(name);

			prefab = block;
		}
		else if (strcmp(type, STAR) == 0)
		{
			Star* star = new Star();
			fscanf(f, "COLLIDER_SIZE %d\n", &number);
			star->SetCollider(number);
			fscanf(f, "RENDERER %s\n", name);
			star->SetRenderer(name);
			star->SetScale(Vector3(0.12, 0.12, 0.12));

			prefab = star;
		}
		else if (strcmp(type, BULLET) == 0)
		{
			Bullet* bullet = new Bullet();
			fscanf(f, "COLLIDER_SIZE %d\n", &number);
			bullet->SetCollider(number);
			fscanf(f, "RENDERER %s\n", name);
			bullet->SetRenderer(name);
			fscanf(f, "SPEED %d\n", &number);
			bullet->SetSpeed(number);

			prefab = bullet;
		}
		else if (strcmp(type, GUN) == 0)
		{
			float atkSpeed;
			Gun* gun = new Gun();
			fscanf(f, "RENDERER %s\n", name);
			gun->SetRenderer(name);
			fscanf(f, "ATTACK_SPEED %f", &atkSpeed);
			gun->SetAttackSpeed(atkSpeed);

			prefab = gun;
		}
		else if (strcmp(type, GUARD) == 0)
		{
			Guard* guard = new Guard();
			fscanf(f, "COLLIDER_SIZE %d\n", &number);
			guard->SetCollider(number);
			fscanf(f, "RENDERER %s\n", name);
			guard->SetRenderer(name);
			fscanf(f, "SPEED %d\n", &number);
			guard->SetSpeed(number);

			prefab = guard;
		}
		else if (strcmp(type, SAW_BLADE) == 0)
		{
			SawBlade* sawBlade = new SawBlade();
			fscanf(f, "COLLIDER_SIZE %d\n", &number);
			sawBlade->SetCollider(number);
			fscanf(f, "RENDERER %s\n", name);
			sawBlade->SetRenderer(name);
			sawBlade->SetScale(Vector3(0.1, 0.1, 0.1));

			prefab = sawBlade;
		}
		else if (strcmp(type, CHASER) == 0)
		{
			Chaser* chaser = new Chaser();
			fscanf(f, "COLLIDER_SIZE %d\n", &number);
			chaser->SetCollider(number);
			fscanf(f, "RENDERER %s\n", name);
			chaser->SetRenderer(name);
			fscanf(f, "SPEED %d\n", &number);
			chaser->SetSpeed(number);
			prefab = chaser;
		}
		else if (strcmp(type, SPINNER) == 0)
		{
			SpinnerFly* spinner = new SpinnerFly();
			fscanf(f, "COLLIDER_SIZE %d\n", &number);
			spinner->SetCollider(number);
			fscanf(f, "RENDERER %s\n", name);
			spinner->SetRenderer(name);
			fscanf(f, "SPEED %d\n", &number);
			spinner->SetSpeed(number);

			prefab = spinner;
		}
		else
		{
			printf("WARNING: prefab %s is not defined\n", type);
			continue;
		}

		stack<GameObject*> pool;
		pool.push(prefab);
		for (int j = 1; j < amount; j++)
			pool.push((GameObject*)prefab->Clone());

		m_Pool[type] = pool;
	}

	fclose(f);
}

GameObject* ObjectPool::GetPooledObject(string objectType)
{
	if (!(m_Pool.count(objectType) > 0))
	{
		printf("WARNING: can't find object with name %s in object pool\n", objectType.c_str());
		return NULL;
	}
	if (m_Pool[objectType].size() <= 0)
	{
		printf("WARNING: out of object %s\n", objectType.c_str());
		return NULL;
	}
	GameObject* object = m_Pool[objectType].top();
	m_Pool[objectType].pop();
	return object;
}

void ObjectPool::ReturnObject(GameObject* object)
{
	if (!(m_Pool.count(object->GetName()) > 0))
	{
		printf("WARNING: can't find object with name %s in object pool\n", object->GetName().c_str());
		return;
	}

	m_Pool[object->GetName()].push(object);
	return;
}

ObjectPool::~ObjectPool()
{
	for (map<string, stack<GameObject*>>::iterator it = m_Pool.begin(); it != m_Pool.end(); ++it) 
	{
		while (!it->second.empty())
		{
			GameObject* object = it->second.top();
			it->second.pop();
			delete object;
		}
	}
}
