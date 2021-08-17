#include "stdafx.h"
#include "LevelState.h"

LevelState::LevelState() 
{
	m_Name = "Level";

	// TO DO: load game object prefabs
	m_bullet = NULL;
	m_i = 0;
	m_Time = 0;
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

	int amount, id, iBool, numBullets;
	float x, y, z, speed;
	char keyword[30], name[20];

	GameObject* blockPrefab = NULL;
	GameObject* playerPrefab = NULL;
	GameObject* bulletPrefab = NULL;
	GameObject* gunPrefab = NULL;

	string path0 = "Managers/GameObjectPrefab.txt";
	FILE* filePre = fopen(path0.c_str(), "r+");

	if (filePre == NULL)
	{
		printf("Invalid file %s\n", path0.c_str());
		exit(1);
	}

	fscanf(filePre, "#PrefabObject: %d\n", &amount);
	
	for (int i = 0; i < amount; i++)
	{
		
		fscanf(filePre, "%s %s\n", keyword, name);

		if (strcmp(name, "Block") == 0)
		{
			Block* block = new Block();
			fscanf(filePre, "COLLIDER_SIZE %f\n", &x);
			block->SetCollider(x);
			fscanf(filePre, "RENDERER %d\n", &id);
			block->SetRenderer(id);
			fscanf(filePre, "SPEED %f\n", &speed);
			blockPrefab = block;
		}

		if (strcmp(name, "Bullet") == 0)
		{
			Bullet* bullet = new Bullet();
			fscanf(filePre, "COLLIDER_SIZE %f\n", &x);
			bullet->SetCollider(x);
			fscanf(filePre, "RENDERER %d\n", &id);
			bullet->SetRenderer(id);
			fscanf(filePre, "SPEED %f\n", &speed);
			bullet->SetSpeed(speed);
			fscanf(filePre, "NUMBER BULLETS %d\n", &numBullets);
			bulletPrefab = bullet;
			m_bullet = bullet;
		}

		if (strcmp(name, "Gun") == 0)
		{
			Gun* gun = new Gun();
			fscanf(filePre, "COLLIDER_SIZE %f\n", &x);
			gun->SetCollider(x);
			fscanf(filePre, "RENDERER %d\n", &id);
			gun->SetRenderer(id);
			fscanf(filePre, "SPEED %f\n", &speed);
			gunPrefab = gun;
		}

		if (strcmp(name, "Player") == 0)
		{
			Player* player = new Player();
			fscanf(filePre, "COLLIDER_SIZE %f\n", &x);
			player->SetCollider(x);
			fscanf(filePre, "RENDERER %d\n", &id);
			player->SetRenderer(id);
			fscanf(filePre, "SPEED %f\n", &speed);
			// Set speed
			playerPrefab = player;
		}
	}

	string path = "Managers/Level3SM.txt";
	FILE* fileMap = fopen(path.c_str(), "r+");
	if (fileMap == NULL)
	{
		printf("Invalid file %s\n", path.c_str());
		exit(1);
	}

	fscanf(fileMap, "#%s\n", keyword);
	if (strcmp(keyword, "Dungeon"))
		printf("WARNING: level format is not correct");

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
				GameObject* block = (GameObject*)blockPrefab->Clone();
				block->SetPosition(Dungeon::GirdToWord(j, Dungeon::Height - i - 1, 0));
				block->CreateCollider();
				m_GameObjects.push_back(block);
			}
			if (iBool == 3)
			{
				playerPrefab->SetPosition(Dungeon::GirdToWord(j, Dungeon::Height - i - 1, 0));
				playerPrefab->CreateCollider();
				m_GameObjects.push_back(playerPrefab);
			}  
			if (iBool == 2)
			{
				GameObject* gun = (GameObject*) gunPrefab->Clone();
				gun->SetPosition(Dungeon::GirdToWord(j, Dungeon::Height - i - 1, 0));
				gun->CreateCollider();
				m_GameObjects.push_back(gun);
			}
		}
	}

	for (int i = 0; i < numBullets; i++)
	{
		Bullet* temp = ((Bullet*)bulletPrefab)->Clone();
		temp->SetPosition(Vector3((i - 5) * 100, 0, 0));
		temp->CreateCollider();
		m_BulletObjects.push_back(temp);
	}

	delete blockPrefab;
	delete bulletPrefab;
	delete gunPrefab;

	fclose(filePre);
	fclose(fileMap);
}

void LevelState::Update(float deltaTime)
{
	m_Time += deltaTime;

	for each (Object * object in m_GameObjects)
		object->Update(deltaTime);
	for each (Object * object in m_BulletObjects)
		object->Update(deltaTime);

	Physic::GetInstance()->Update(deltaTime);
}

void LevelState::Draw()
{
	for each (Object * object in m_BulletObjects)
		object->Draw();

	for each (Object * object in m_GameObjects)
		object->Draw();
}

LevelState::~LevelState()
{
	for each (Object * object in m_GameObjects)
		delete object;

	for each (Object * object in m_BulletObjects)
		delete object;
}