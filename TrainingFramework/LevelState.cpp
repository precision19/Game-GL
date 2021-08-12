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

	string path = "Managers/Level3SM.txt";
	FILE* f = fopen(path.c_str(), "r+");
	if (f == NULL)
	{
		printf("Invalid file %s\n", path.c_str());
		exit(1);
	}

	int amount, id, iBool;
	float x, y;
	char keyword[30], type[10];

	fscanf(f, "#%s\n", keyword);
	if (strcmp(keyword, "Dungeon"))
		printf("WARNING: level format is not correct");

	fscanf(f, "TYPE %s\n", type);
	Object* blockPrefab = new Object("Block");
	fscanf(f, "RENDERER %d\n", &id);
	blockPrefab->SetRenderer(id);
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

			if (iBool)
			{
				Object* block = blockPrefab->Clone();
				block->SetPosition(Dungeon::GirdToWord(j, Dungeon::Height - i - 1, 0));
				m_GameObjects.push_back(block);
			}
		}
	}

	delete blockPrefab;

	fclose(f);
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