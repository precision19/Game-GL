#include "stdafx.h"
#include "PrefabManager.h"

PrefabManager* PrefabManager::ms_Instance = NULL;

void PrefabManager::CreateInstance()
{
	if (ms_Instance == NULL)
		ms_Instance = new PrefabManager();
}

PrefabManager* PrefabManager::GetInstance()
{
	return ms_Instance;
}

void PrefabManager::DestroyInstance()
{
	if (ms_Instance)
	{
		delete ms_Instance;
		ms_Instance = NULL;
	}
}

PrefabManager::PrefabManager()
{
}

void PrefabManager::LoadPrefabs(string sceneName)
{
	DestroyAllPrefab();

	string path = "Managers/" + sceneName + "PM.txt";

	FILE* f = fopen(path.c_str(), "r+");

	if (f == NULL)
	{
		printf("Invalid file %s\n", path.c_str());
		exit(1);
	}

	int amount;
	char keyword[20];

	fscanf(f, "#Renderers: %d\n", &amount);
	for (int i = 0; i < amount; i++)
	{
		int id;
		fscanf(f, "ID %d\n", &id);
		if (id != i)
		{
			printf("WARNING: Renderer's ID is not correct");
		}

		Renderer* renderer = NULL;

		fscanf(f, "TYPE %s\n", keyword);
		if (strcmp(keyword, "SPRITE") == 0)
		{
			renderer = new Renderer2D();
		}
		else 
		{
			printf("Normal");
			renderer = new Renderer();
			fscanf(f, "MODEL %d\n", &id);
			renderer->SetModel(id);
			fscanf(f, "SHADERS %d\n", &id);
			renderer->SetShaders(id);
		}

		int amount2;
		fscanf(f, "AMOUNT_OF_TEXTURES %d\n", &amount2);

		for (int j = 0; j < amount2; j++)
		{
			if (j != amount2 - 1)
			{
				fscanf(f, "%d ", &id);
				renderer->SetTexture(id);
			}
			else
			{
				fscanf(f, "%d\n", &id);
				renderer->SetTexture(id);
			}

		}
		if (amount2 > 1)
		{
			int frameRate;
			fscanf(f, "FRAME_RATE %d\n", &frameRate);
			// TODO: Set frame rate of renderer
		}
		m_Renderers.push_back(renderer);
	}

	fclose(f);
}

Renderer* PrefabManager::GetRenderer(int id)
{
	if (id < 0 || id >= m_Renderers.size())
	{
		printf("ERROR:");
		return NULL;
	}
	return m_Renderers.at(id);
}

void PrefabManager::DestroyAllPrefab()
{
	for (int i = 0; i < m_Renderers.size(); i++)
	{
		delete m_Renderers.at(i);
	}
	
	m_Renderers.clear();
}

PrefabManager::~PrefabManager()
{
	DestroyAllPrefab();
}
