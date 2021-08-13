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
	char keyword[30], type[10];

	Object* objectPrefab = new Object();
	Object* trap = new Trap();

	string path0 = "Managers/GameObjectPrefab.txt";
	FILE* file = fopen(path0.c_str(), "r+");

	if (file == NULL)
	{
		printf("Invalid file %s\n", path0.c_str());
		exit(1);
	}

	fscanf(file, "#%s %d\n", keyword, &amount);
	
	for (int i = 0; i < amount; i++)
	{
		
		fscanf(file, "ID %d\n", &id);

		fscanf(file, "TYPE %s\n", type);

		if (!strcmp(type, "GROUND"))
		{
			Object* test = new Object();
			fscanf(file, "SCALE %f %f %f\n", &x, &y, &z);
			test->SetScale(Vector3(x, y, z));

			fscanf(file, "RENDERER %d\n", &id);
			test->SetRenderer(id);
			objectPrefab = test;
		}
		else
		{
			Object* test = new Trap();
			fscanf(file, "SCALE %f %f %f\n", &x, &y, &z);
			test->SetScale(Vector3(x, y, z));

			fscanf(file, "RENDERER %d\n", &id);
			test->SetRenderer(id);
			trap = test;
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
				Object* block = objectPrefab->Clone();
				block->SetPosition(Dungeon::GirdToWord(j, Dungeon::Height - i - 1, 0));
				m_GameObjects.push_back(block);
			}
			if (iBool == 2)
			{
				Object* block = trap->Clone();
				block->SetPosition(Dungeon::GirdToWord(j, Dungeon::Height - i - 1, 0));
				m_GameObjects.push_back(block);
			}  
		}
	}

	delete trap;
	delete objectPrefab;
	fclose(f);
	fclose(file);
}

void LevelState::CreateDungeon(Object* block)
{

}

void LevelState::Update(float deltaTime)
{
	/*for each (Object * obj in m_GameObjects)
		obj->Update(deltaTime);*/

	for (int i = 0; i < m_GameObjects.size(); i++)
		m_GameObjects.at(i)->Update(deltaTime);
}

void LevelState::Draw()
{
	for (int i = 0; i < m_GameObjects.size(); i++)
		m_GameObjects.at(i)->Draw();
}

LevelState::~LevelState()
{
	for (int i = 0; i < m_GameObjects.size(); i++)
		delete m_GameObjects.at(i);
}