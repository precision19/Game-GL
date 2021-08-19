#include "stdafx.h"
#include "LevelState.h"

LevelState::LevelState() 
{
	m_Name = "Level";

	// TO DO: load game object prefabs
	string path0 = "Managers/GameObjectPrefab.txt";
	FILE* f = fopen(path0.c_str(), "r+");

	if (f == NULL)
	{
		printf("Invalid file %s\n", path0.c_str());
		exit(1);
	}
	char keyword[20], name[20];
	int amount, number;
	fscanf(f, "#PrefabObject: %d\n", &amount);

	for (int i = 0; i < amount; i++)
	{

		fscanf(f, "%s %s\n", keyword, name);

		if (strcmp(name, "Block") == 0)
		{
			m_BlockPrefab = new Block();
			fscanf(f, "COLLIDER_SIZE %d\n", &number);
			m_BlockPrefab->SetCollider(number);
			fscanf(f, "RENDERER %s\n", name);
			m_BlockPrefab->SetRenderer(name);
		}
		else if (strcmp(name, "Bullet") == 0)
		{
			m_BulletPrefab = new Bullet();
			fscanf(f, "COLLIDER_SIZE %d\n", &number);
			m_BulletPrefab->SetCollider(number);
			fscanf(f, "RENDERER %s\n", name);
			m_BulletPrefab->SetRenderer(name);
			fscanf(f, "SPEED %d\n", &number);
			m_BulletPrefab->SetSpeed(number);			
		}
		else if (strcmp(name, "Gun") == 0)
		{
			m_GunPrefab = new Gun();
			fscanf(f, "RENDERER %s\n", name);
			m_GunPrefab->SetRenderer(name);
		}
		else if (strcmp(name, "Player") == 0)
		{
			m_Player = new Player();
			fscanf(f, "COLLIDER_SIZE %d\n", &number);
			m_Player->SetCollider(number);
			fscanf(f, "RENDERER %s\n", name);
			m_Player->SetRenderer(name);
			fscanf(f, "RENDERER %s\n", name);
			m_Player->SetRenderer(name);
			fscanf(f, "RENDERER %s\n", name);
			m_Player->SetRenderer(name);
			fscanf(f, "RENDERER %s\n", name);
			m_Player->SetRenderer(name);
			fscanf(f, "RENDERER %s\n", name);
			m_Player->SetRenderer(name);
			fscanf(f, "SPEED %d\n", &number);
			m_Player->SetSpeed(number);
			// Set speed
			fscanf(f, "JUMP_FORCE %d\n", &number);
			m_Player->SetJumpForce(number);
		}
		else if (strcmp(name, "Gate") == 0)
		{
			m_Gate = new Object();
			fscanf(f, "RENDERER %s\n", name);
			m_Gate->SetRenderer(name);
		}
		else if (strcmp(name, "Guard") == 0)
		{
			m_GuardPrefab = new Guard();
			fscanf(f, "COLLIDER_SIZE %d\n", &number);
			m_GuardPrefab->SetCollider(number);
			fscanf(f, "RENDERER %s\n", name);
			m_GuardPrefab->SetRenderer(name);
			fscanf(f, "SPEED %d\n", &number);
			m_GuardPrefab->SetSpeed(number);
		}

		if (strcmp(name, "Star") == 0)
		{
			m_StarPrefab = new Star();
			fscanf(f, "COLLIDER_SIZE %d\n", &number);
			m_StarPrefab->SetCollider(number);
			fscanf(f, "RENDERER %s\n", name);
			m_StarPrefab->SetRenderer(name);
			m_StarPrefab->SetScale(Vector3(0.12, 0.12, 0.12));
		}

		if (strcmp(name, "SawBlade") == 0)
		{
			m_SawPrefab = new SawBlade();
			fscanf(f, "COLLIDER_SIZE %d\n", &number);
			m_SawPrefab->SetCollider(number);
			fscanf(f, "RENDERER %s\n", name);
			m_SawPrefab->SetRenderer(name);
			m_SawPrefab->SetScale(Vector3(0.1, 0.1, 0.1));
		}

		if (strcmp(name, "TreasureChest") == 0)
		{
			m_Chest = new TreasureChest();
			fscanf(f, "COLLIDER_SIZE %d\n", &number);
			m_Chest->SetCollider(number);
			fscanf(f, "RENDERER %s\n", name);
			m_Chest->SetRenderer(name);
			fscanf(f, "RENDERER %s\n", name);
			m_Chest->SetRenderer(name);
		}
	}

	fclose(f);
}

void LevelState::SetStateManager(StateManager* stateManager)
{
	m_StateManager = stateManager;
}

void LevelState::OnStart()
{
	// TODO: goi PlayerPrefs de lay data
	// DestroyAllObjects();
	Camera::GetInstance()->SetDefault();
	AudioManager::GetInstance()->PlayBackgroundMusic(m_Name);

	int amount, id, iBool, numBullets;
	float x, y, z, speed;
	char keyword[30], name[20];

	string path = "Managers/Level3SM.txt";
	FILE* fileMap = fopen(path.c_str(), "r+");
	if (fileMap == NULL)
	{
		printf("Invalid file %s\n", path.c_str());
		exit(1);
	}

	fscanf(fileMap, "#Objects: %d\n", &amount);

	for (int i = 0; i < amount; i++)
	{
		fscanf(fileMap, "%s %s\n", keyword, name);

		if (strcmp(name, "Dungeon") == 0)
		{
			for (int i = -1; i <= Dungeon::Height; i++)
			{
				for (int j = -1; j <= Dungeon::Width; j++)
				{
					if (j == Dungeon::Width - 1)
					{
						fscanf(fileMap, "%d\n", &iBool);
					}
					else 
					{
						fscanf(fileMap, "%d ", &iBool);
					}

					if (iBool == 1)
					{
						GameObject* block = (GameObject*)m_BlockPrefab->Clone();
						block->SetPosition(Dungeon::GirdToWord(j, Dungeon::Height - i - 1, 1));
						block->CreateCollider();
						m_GameObjects.push_back(block);
					}
					else if (iBool == 2)
					{
						GameObject* gun = (GameObject*) m_GunPrefab->Clone();
						gun->SetPosition(Dungeon::GirdToWord(j, Dungeon::Height - i - 1, 0));
						gun->CreateCollider();
						m_GameObjects.push_back(gun);
					}
					else if (iBool == 3)
					{
						m_Gate->SetPosition(Dungeon::GridToWorld(j, Dungeon::Height - i - 1));
						m_Player->SetPosition(Dungeon::GridToWorld(j, Dungeon::Height - i - 1));
						m_Player->CreateCollider();
					}
					else if (iBool == 4)
					{
						Guard* guard = m_GuardPrefab->Clone();
						guard->SetPosition(Dungeon::GirdToWord(j, Dungeon::Height - i - 1, 0));
						guard->SetPositionStart(Dungeon::GirdToWord(j, Dungeon::Height - i - 1, 0));
						guard->SetPositionEnd(Dungeon::GirdToWord(j + 1, Dungeon::Height - i - 1, 0));
						guard->CreateCollider();
						m_GameObjects.push_back(guard);
					}

					if (iBool == 5)
					{
						GameObject* star = (GameObject*)m_StarPrefab->Clone();
						star->SetPosition(Dungeon::GirdToWord(j, Dungeon::Height - i - 1, 0));
						star->CreateCollider();
						m_GameObjects.push_back(star);
					}

					if (iBool == 6)
					{
						GameObject* blade = (GameObject*)m_SawPrefab->Clone();
						blade->SetPosition(Dungeon::GirdToWord(j, Dungeon::Height - i - 1, 0));
						blade->CreateCollider();
						m_GameObjects.push_back(blade);
					}

					if (iBool == 7)
					{
						m_Chest->SetPosition(Dungeon::GirdToWord(j, Dungeon::Height - i - 1, 0));
						m_Chest->CreateCollider();
					}
				}
			}
		}
		else if (strcmp(name, "Gate") == 0)
		{
			
		}
		else
		{
			Object* object = new Object(name);

			fscanf(fileMap, "RENDERER %s\n", name);
			object->SetRenderer(name);
			fscanf(fileMap, "POSITION %f %f %f\n", &x, &y, &z);
			object->SetPosition(Vector3(x, y, z));
			fscanf(fileMap, "ROTATION %f %f %f\n", &x, &y, &z);
			object->SetRotation(Vector3(x, y, z));
			fscanf(fileMap, "SCALE %f %f %f\n", &x, &y, &z);
			object->SetScale(Vector3(x, y, z));

			m_GameObjects.push_back(object);
		}
	}

	fclose(fileMap);
}

void LevelState::Restart()
{

}

void LevelState::Update(float deltaTime)
{
	for each (Object * object in m_GameObjects)
		object->Update(deltaTime);

	m_Player->Update(deltaTime);
	m_Chest->Update(deltaTime);

	Physic::GetInstance()->Update(deltaTime);
}

void LevelState::Draw()
{
	for each (Object * object in m_GameObjects)
		object->Draw();

	m_Gate->Draw();
	m_Player->Draw();
	m_Chest->Draw();
}

LevelState::~LevelState()
{
	//for each (Object * object in m_GameObjects)
	//	delete object;
	for (int i = 0; i < m_GameObjects.size(); i++)
		delete m_GameObjects.at(i);

	for each (Object * object in m_BulletObjects)
		delete object;

	for each (Object * object in m_Decorations)
		delete object;

	delete m_Player;
	delete m_Gate;
	delete m_Chest;
	delete m_BlockPrefab;
	delete m_StarPrefab;
	delete m_SawPrefab;
	delete m_GuardPrefab;
	delete m_GunPrefab;
	delete m_BulletPrefab;
}