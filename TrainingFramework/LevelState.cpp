#include "stdafx.h"
#include "LevelState.h"

LevelState::LevelState() 
{
	m_Name = "Level";
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

	int amount, id, iBool;
	float x, y, z;
	char keyword[30], name[20];

	GameObject* blockPrefab = NULL;
	GameObject* playerPrefab = NULL;

	string path0 = "Managers/GameObjectPrefab.txt";
	FILE* file = fopen(path0.c_str(), "r+");

	if (file == NULL)
	{
		printf("Invalid file %s\n", path0.c_str());
		exit(1);
	}

	fscanf(file, "#PrefabObject: %d\n", &amount);
	
	for (int i = 0; i < amount; i++)
	{
		
		fscanf(file, "%s %s\n", keyword, name);

		if (strcmp(name, "Block") == 0)
		{
			Block* block = new Block();
			fscanf(file, "COLLIDER_SIZE %f\n", &x);
			block->SetCollider(x);
			fscanf(file, "RENDERER %d\n", &id);
			block->SetRenderer(id);
			blockPrefab = block;
		}
		else
		{
			Player* player = new Player();
			fscanf(file, "COLLIDER_SIZE %f\n", &x);
			player->SetCollider(x);
			fscanf(file, "RENDERER %d\n", &id);
			player->SetRenderer(id);
			playerPrefab = player;
		}
	}

	string path = "Managers/Level3SM.txt";
	FILE* f = fopen(path.c_str(), "r+");
	if (f == NULL)
	{
		printf("Invalid file %s\n", path.c_str());
		exit(1);
	}

	fscanf(f, "#%s\n", keyword);
	if (strcmp(keyword, "Dungeon"))
		printf("WARNING: level format is not correct");

	for (int i = -1; i <= Dungeon::Height; i++)
	{
		for (int j = -1; j <= Dungeon::Width; j++)
		{
			if (j == Dungeon::Width - 1)
			{
				fscanf(f, "%d\n", &iBool);
			}
			else 
			{
				fscanf(f, "%d ", &iBool);
			}

			if (iBool == 1)
			{
				GameObject* block = (GameObject*)blockPrefab->Clone();
				block->SetPosition(Dungeon::GirdToWord(j, Dungeon::Height - i - 1, 0));
				block->CreateCollider();
				m_GameObjects.push_back(block);
			}
			if (iBool == 2)
			{
				playerPrefab->SetPosition(Dungeon::GirdToWord(j, Dungeon::Height - i - 1, 0));
				playerPrefab->CreateCollider();
				m_GameObjects.push_back(playerPrefab);
			}  
		}
	}

	delete blockPrefab;

	fclose(f);
	fclose(file);
}

void LevelState::Update(float deltaTime)
{
	Physic::GetInstance()->Update(deltaTime);

	for each (Object * object in m_GameObjects) {
		object->Update(deltaTime);
	}

}

void LevelState::Draw()
{
	for each (Object * object in m_GameObjects)
		object->Draw();
}

LevelState::~LevelState()
{
	for each (Object * object in m_GameObjects)
		delete object;
}