#include "stdafx.h"
#include "LevelState.h"
#include "EffectManager.h"

LevelState::LevelState() 
{
	m_Name = "Level";
	m_LevelID = 1;
	m_Score = 0;
	m_ScoreEnd = 0;

	//// TO DO: load game object prefabs
	//string path0 = "Managers/GameObjectPrefab.txt";
	//FILE* f = fopen(path0.c_str(), "r+");
	//if (f == NULL)
	//{
	//	printf("Invalid file %s\n", path0.c_str());
	//	exit(1);
	//}
	//char keyword[20], name[20];
	//int amount, number;
	//fscanf(f, "#PrefabObject: %d\n", &amount);
	//for (int i = 0; i < amount; i++)
	//{
	//	fscanf(f, "%s %s\n", keyword, name);
	//	if (strcmp(name, "Block") == 0)
	//	{
	//		m_BlockPrefab = new Block();
	//		fscanf(f, "COLLIDER_SIZE %d\n", &number);
	//		m_BlockPrefab->SetCollider(number);
	//		fscanf(f, "RENDERER %s\n", name);
	//		m_BlockPrefab->SetRenderer(name);
	//	}
	//	else if (strcmp(name, "Bullet") == 0)
	//	{
	//		m_BulletPrefab = new Bullet();
	//		fscanf(f, "COLLIDER_SIZE %d\n", &number);
	//		m_BulletPrefab->SetCollider(number);
	//		fscanf(f, "RENDERER %s\n", name);
	//		m_BulletPrefab->SetRenderer(name);
	//		fscanf(f, "SPEED %d\n", &number);
	//		m_BulletPrefab->SetSpeed(number);			
	//	}
	//	else if (strcmp(name, "Gun") == 0)
	//	{
	//		m_GunPrefab = new Gun();
	//		fscanf(f, "RENDERER %s\n", name);
	//		m_GunPrefab->SetRenderer(name);
	//	}
	//	else if (strcmp(name, "Player") == 0)
	//	{
	//		//m_Player = new Player();
	//		fscanf(f, "COLLIDER_SIZE %d\n", &number);
	//		//m_Player->SetCollider(number);
	//		fscanf(f, "RENDERER %s\n", name);
	//		//m_Player->SetRenderer(name);
	//		fscanf(f, "RENDERER %s\n", name);
	//		//m_Player->SetRenderer(name);
	//		fscanf(f, "RENDERER %s\n", name);
	//		//m_Player->SetRenderer(name);
	//		fscanf(f, "RENDERER %s\n", name);
	//		//m_Player->SetRenderer(name);
	//		fscanf(f, "RENDERER %s\n", name);
	//		//m_Player->SetRenderer(name);
	//		fscanf(f, "SPEED %d\n", &number);
	//		//m_Player->SetSpeed(number);
	//		// Set speed
	//		fscanf(f, "JUMP_FORCE %d\n", &number);
	//		//m_Player->SetJumpForce(number);
	//	}
	//	else if (strcmp(name, "Gate") == 0)
	//	{
	//		//m_Gate = new Object();
	//		fscanf(f, "RENDERER %s\n", name);
	//		//m_Gate->SetRenderer(name);
	//	}
	//	else if (strcmp(name, "Guard") == 0)
	//	{
	//		m_GuardPrefab = new Guard();
	//		fscanf(f, "COLLIDER_SIZE %d\n", &number);
	//		m_GuardPrefab->SetCollider(number);
	//		fscanf(f, "RENDERER %s\n", name);
	//		m_GuardPrefab->SetRenderer(name);
	//		fscanf(f, "SPEED %d\n", &number);
	//		m_GuardPrefab->SetSpeed(number);
	//	}
	//	if (strcmp(name, "Star") == 0)
	//	{
	//		m_StarPrefab = new Star();
	//		fscanf(f, "COLLIDER_SIZE %d\n", &number);
	//		m_StarPrefab->SetCollider(number);
	//		fscanf(f, "RENDERER %s\n", name);
	//		m_StarPrefab->SetRenderer(name);
	//		m_StarPrefab->SetScale(Vector3(0.12, 0.12, 0.12));
	//	}
	//	if (strcmp(name, "SawBlade") == 0)
	//	{
	//		m_SawPrefab = new SawBlade();
	//		fscanf(f, "COLLIDER_SIZE %d\n", &number);
	//		m_SawPrefab->SetCollider(number);
	//		fscanf(f, "RENDERER %s\n", name);
	//		m_SawPrefab->SetRenderer(name);
	//		m_SawPrefab->SetScale(Vector3(0.1, 0.1, 0.1));
	//	}
	//	if (strcmp(name, "TreasureChest") == 0)
	//	{
	//		//m_Chest = new TreasureChest();
	//		fscanf(f, "COLLIDER_SIZE %d\n", &number);
	//		//m_Chest->SetCollider(number);
	//		fscanf(f, "RENDERER %s\n", name);
	//		//m_Chest->SetRenderer(name);
	//		fscanf(f, "RENDERER %s\n", name);
	//		//m_Chest->SetRenderer(name);
	//	}
	//	if (strcmp(name, "Chaser") == 0)
	//	{
	//		m_Chaser = new Chaser();
	//		fscanf(f, "COLLIDER_SIZE %d\n", &number);
	//		m_Chaser->SetCollider(number);
	//		fscanf(f, "RENDERER %s\n", name);
	//		m_Chaser->SetRenderer(name);
	//		m_Chaser->SetScale(Vector3(0.4, 0.4, 0.4));
	//	}
	//	if (strcmp(name, "Spinner") == 0)
	//	{
	//		m_SpinnerPrefab = new SpinnerFly();
	//		fscanf(f, "COLLIDER_SIZE %d\n", &number);
	//		m_SpinnerPrefab->SetCollider(number);
	//		fscanf(f, "RENDERER %s\n", name);
	//		m_SpinnerPrefab->SetRenderer(name);
	//		fscanf(f, "SPEED %d\n", &number);
	//		m_SpinnerPrefab->SetSpeed(number * PI / 180);
	//	}
	//}
	//fclose(f);
}

int LevelState::GetLevel()
{
	return m_LevelID;
}

void LevelState::SetStateManager(StateManager* stateManager)
{
	m_StateManager = stateManager;
}

void LevelState::SetLevel(int levelID) 
{
	m_LevelID = levelID;
}

void LevelState::OnStart()
{
	printf("open level %d\n", m_LevelID);
	Camera::GetInstance()->SetDefault();
	AudioManager::GetInstance()->PlayBackgroundMusic(m_Name);
	LoadLevel();
}

void LevelState::LoadLevel()
{
	m_Player = (Player*)ObjectPool::GetInstance()->GetPooledObject(PLAYER);
	m_Gate = ObjectPool::GetInstance()->GetPooledObject(GATE);
	m_Chest = (TreasureChest*)ObjectPool::GetInstance()->GetPooledObject(TREASURE_CHEST);
	AudioManager::GetInstance()->PlaySoundEffect("Ambiance", true, 20.0f);
	int amount, id, iBool, numBullets;
	float x, y, z, speed;
	char keyword[30], name[20];

	string path = "Managers/Level" + to_string(m_LevelID) + "SM.txt";
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
						//GameObject* block = (GameObject*)m_BlockPrefab->Clone();
						GameObject* block = ObjectPool::GetInstance()->GetPooledObject(BLOCK);
						block->SetPosition(Dungeon::GirdToWord(j, Dungeon::Height - i - 1, 1));
						block->CreateCollider();
						m_GameObjects.push_back(block);
					}

					else if (iBool == 3)
					{
						m_Gate->SetPosition(Dungeon::GridToWorld(j, Dungeon::Height - i - 1));
						m_GameObjects.push_back(m_Gate);

						m_Player->SetPosition(Dungeon::GridToWorld(j, Dungeon::Height - i - 1));
						m_Player->CreateCollider();
						m_GameObjects.push_back(m_Player);
					}

					if (iBool == 5)
					{
						//GameObject* star = (GameObject*)m_StarPrefab->Clone();
						GameObject* star = ObjectPool::GetInstance()->GetPooledObject(STAR);
						star->SetPosition(Dungeon::GirdToWord(j, Dungeon::Height - i - 1, 0));
						star->CreateCollider();
						m_GameObjects.push_back(star);
						//star->GetRenderer()->SetOpacity(0.0f);
						//EffectManager::GetInstance()->o.push_back(star);
					}

					if (iBool == 7)
					{
						m_Chest->SetPosition(Dungeon::GirdToWord(j, Dungeon::Height - i - 1, 0));
						m_Chest->CreateCollider();
						m_Chest->GetRenderer()->SetOpacity(0.0f);
						m_GameObjects.push_back(m_Chest);
						
					}
				}
			}
		}

		else if (strcmp(name, "Gun") == 0)
		{
			GameObject* gun = ObjectPool::GetInstance()->GetPooledObject(GUN);
			fscanf(fileMap, "POSITION %f %f\n", &x, &y);
			gun->SetPosition(Dungeon::GirdToWord(x, y, 0));
			gun->CreateCollider();
			m_GameObjects.push_back(gun);
		}

		else if (strcmp(name, "Chaser") == 0)
		{
			fscanf(fileMap, "NUMBERCHASERS %d\n", &iBool);
			for (int i = 0; i < iBool; i++)
			{
				Chaser* chaser = (Chaser*)ObjectPool::GetInstance()->GetPooledObject(CHASER);
				fscanf(fileMap, "POSITION %f %f\n", &x, &y);
				chaser->SetPosition(Dungeon::GirdToWord(x, y, 0));
				chaser->SetPositionStart(Dungeon::GirdToWord(x, y, 0));
				chaser->SetPositionTarget(Vector2(0.0f, 0.0f));
				chaser->SetScale(Vector3(0.35, 0.35, 0.35));
				chaser->CreateCollider();
				m_GameObjects.push_back(chaser);
			}
		}

		else if (strcmp(name, "SawBlade") == 0)
		{
			fscanf(fileMap, "NUMBERBLADES %d\n", &iBool);
			for (int i = 0; i < iBool; i++)
			{
				//Guard* guard = m_GuardPrefab->Clone();
				SawBlade* blade = (SawBlade*)ObjectPool::GetInstance()->GetPooledObject(SAW_BLADE);
				fscanf(fileMap, "POSITION %f %f\n", &x, &y);
				blade->SetPosition(Dungeon::GirdToWord(x, y, 0));
				blade->CreateCollider();
				m_GameObjects.push_back(blade);
			}
		}

		else if (strcmp(name, "Guard") == 0)
		{
			fscanf(fileMap, "NUMBERGUARDS %d\n", &iBool);
			printf("%d", iBool);
			for (int i = 0; i < iBool; i++)
			{
				Guard* guard = (Guard*)ObjectPool::GetInstance()->GetPooledObject(GUARD);
				fscanf(fileMap, "POSITIONSTART %f %f\n", &x, &y);
				guard->SetPosition(Dungeon::GirdToWord(x, y, 0));
				guard->SetPositionStart(Dungeon::GirdToWord(x, y, 0));
				fscanf(fileMap, "POSITIONEND %f %f\n", &x, &y);
				guard->SetPositionEnd(Dungeon::GirdToWord(x, y, 0));
				guard->CreateCollider();
				m_GameObjects.push_back(guard);
			}
		}
		else if (strcmp(name, "Spinner") == 0)
		{
			fscanf(fileMap, "NUMBERSPINNERS %d\n", &iBool);
			for (int i = 0; i < iBool; i++)
			{
				SpinnerFly* spinner = (SpinnerFly*)ObjectPool::GetInstance()->GetPooledObject(SPINNER);
				fscanf(fileMap, "POSITION %f %f\n", &x, &y);
				spinner->SetPosition(Dungeon::GirdToWord(x, y, 0));
				fscanf(fileMap, "POSITIONCENTER %f %f\n", &x, &y);
				spinner->SetPositionCenter(Dungeon::GirdToWord(x, y, 0));
				spinner->SetRadius();
				spinner->SetScale(Vector3(0.3, 0.3, 0.3));
				spinner->CreateCollider();
				m_GameObjects.push_back(spinner);
			}		
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

			m_Backgrounds.push_back(object);
		}
	}

	fclose(fileMap);

	FlagManager::GetInstance()->Set(FLAG_GAME_STATUS, GAME_ON_READY);
}

void LevelState::Restart()
{
	for each (GameObject * object in m_GameObjects)
		object->Reset();
}

void LevelState::Update(float deltaTime)
{
	if (FlagManager::GetInstance()->Check(FLAG_GAME_STATUS, GAME_ON_WIN))
	{
		ClearLevel();
		m_ScoreEnd = m_Score;
		PlayerPrefs::GetInstance()->SetData(m_LevelID, m_ScoreEnd);
		PlayerPrefs::GetInstance()->SaveData();
		m_LevelID++;
		LoadLevel();
		m_Score = 0;
		return;
	}

	if (EventManager::GetInstance()->CheckEvent(EVENT_GROUP_GAMEPLAY, EVENT_PLAYER_DIE))
	{
		Restart();
		m_Score = 0;
	}

	for each (Object * object in m_Backgrounds)
		object->Update(deltaTime);

	for each (GameObject * object in m_GameObjects)
		object->Update(deltaTime);

	if (FlagManager::GetInstance()->Check(FLAG_GAME_STATUS, GAME_ON_PLAYING, GAME_ON_READY))
		Physic::GetInstance()->Update(deltaTime);

	if (EventManager::GetInstance()->CheckEvent(EVENT_GROUP_GAMEPLAY, EVENT_PLAYER_SCORE))
	{
		m_Score++;
	} 
}

void LevelState::Draw()
{
	for each (Object * object in m_Backgrounds)
		object->Draw();

	for each (GameObject * object in m_GameObjects)
		object->Draw();
}

void LevelState::ClearLevel() 
{
	for each (Object * object in m_Backgrounds)
		delete object;
	m_Backgrounds.clear();
	for each (GameObject * object in m_GameObjects)
	{
		object->DestroyCollider();
		ObjectPool::GetInstance()->ReturnObject(object);
	}
	m_GameObjects.clear();
}

LevelState::~LevelState()
{
	for each (Object * object in m_Backgrounds)
		delete object;

	for each (Object * object in m_GameObjects)
		delete object;
}