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
	string path = "Managers/PM.txt";

	FILE* f = fopen(path.c_str(), "r+");

	if (f == NULL)
	{
		printf("Invalid file %s\n", path.c_str());
		exit(1);
	}

	int amount, id;
	char keyword[20], name[20];

	fscanf(f, "#Renderers: %d\n", &amount);
	for (int i = 0; i < amount; i++)
	{
		fscanf(f, "%s %s\n", keyword, name);
		Renderer* renderer = NULL;

		fscanf(f, "TYPE %s\n", keyword);
		if (strcmp(keyword, "2D") == 0)
		{
			renderer = new Renderer2D();
			fscanf(f, "MODEL %d\n", &id);
			renderer->SetModel(id);
			fscanf(f, "SHADER %d\n", &id);
			renderer->SetShaders(id);
			fscanf(f, "TEXTURE %d\n", &id);
			renderer->SetTexture(id);
		}
		else if (strcmp(keyword, "2D_ANIMATION") == 0)
		{
			int frameAmount, fps, iBool;
			renderer = new Animation2D();
			fscanf(f, "MODEL %d\n", &id);
			renderer->SetModel(id);
			fscanf(f, "SHADER %d\n", &id);
			renderer->SetShaders(id);
			fscanf(f, "FRAMES %d\n", &frameAmount);
			for (int i = 0; i < frameAmount; i++)
			{
				if (i == frameAmount - 1)
				{
					fscanf(f, "%d\n", &id);
					((Animation2D*)renderer)->SetTexture(id);
				}
				fscanf(f, "%d ", &id);
				((Animation2D*)renderer)->SetTexture(id);
			}
			fscanf(f, "FPS %d\n", &fps);
			((Animation2D*)renderer)->SetFPS(fps);
			fscanf(f, "LOOP %d\n", &iBool);
			((Animation2D*)renderer)->SetLoop(iBool);
		}
		else
		{
			renderer = new Renderer();
			fscanf(f, "MODEL %d\n", &id);
			renderer->SetModel(id);
			fscanf(f, "SHADER %d\n", &id);
			renderer->SetShaders(id);
			fscanf(f, "TEXTURES %d\n", &id);
			renderer->SetTexture(id);
		}

		m_Renderers.push_back(renderer);
	}
	fclose(f);
}

void PrefabManager::LoadPrefabs(string sceneName)
{
	DestroyAllPrefab();

	string path = "Managers/PM.txt";

	FILE* f = fopen(path.c_str(), "r+");

	if (f == NULL)
	{
		printf("Invalid file %s\n", path.c_str());
		exit(1);
	}

	int amount, id;
	char keyword[20], name[20];

	fscanf(f, "#Renderers: %d\n", &amount);
	for (int i = 0; i < amount; i++)
	{
		fscanf(f, "%s %s\n", keyword, name);
		Renderer* renderer = NULL;

		fscanf(f, "TYPE %s\n", keyword);
		if (strcmp(keyword, "2D") == 0)
		{
			renderer = new Renderer2D();
			fscanf(f, "MODEL %d\n", &id);
			renderer->SetModel(id);
			fscanf(f, "SHADER %d\n", &id);
			renderer->SetShaders(id);
			fscanf(f, "TEXTURE %d\n", &id);
			renderer->SetTexture(id);
		}
		else if (strcmp(keyword, "2D_ANIMATION") == 0)
		{
			int frameAmount, fps, iBool;
			renderer = new Animation2D();
			fscanf(f, "MODEL %d\n", &id);
			renderer->SetModel(id);
			fscanf(f, "SHADER %d\n", &id);
			renderer->SetShaders(id);
			fscanf(f, "FRAMES %d\n", &frameAmount);
			for (int i = 0; i < frameAmount; i++)
			{
				if (i == frameAmount - 1)
				{
					fscanf(f, "%d\n", &id);
					((Animation2D*)renderer)->SetTexture(id);
				}
				fscanf(f, "%d ", &id);
				((Animation2D*)renderer)->SetTexture(id);
			}
			fscanf(f, "FPS %d\n", &fps);
			((Animation2D*)renderer)->SetFPS(fps);
			fscanf(f, "LOOP %d\n", &iBool);
			((Animation2D*)renderer)->SetLoop(iBool);
		}
		else
		{
			renderer = new Renderer();
			fscanf(f, "MODEL %d\n", &id);
			renderer->SetModel(id);
			fscanf(f, "SHADER %d\n", &id);
			renderer->SetShaders(id);
			fscanf(f, "TEXTURES %d\n", &id);
			renderer->SetTexture(id);
		}

		m_Renderers.push_back(renderer);
	}
	fclose(f);
}

Renderer* PrefabManager::GetRenderer(int id)
{
	if (id < 0 || id >= m_Renderers.size())
	{
		printf("ERROR: can not find renderer");
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
