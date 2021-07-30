#include "stdafx.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::ms_Instance = NULL;

void ResourceManager::CreateInstance()
{
	if (ms_Instance == NULL)
		ms_Instance = new ResourceManager();

}

ResourceManager* ResourceManager::GetInstance()
{
	return ms_Instance;
}

void ResourceManager::DestroyInstance()
{
	if (ms_Instance)
	{
		delete ms_Instance;
		ms_Instance = NULL;
	}
}

ResourceManager::ResourceManager()
{
	ifstream ifile;
	ifile.open("Managers/RM.txt");

	if (ifile.fail())
	{
		printf("Invalid File Name!");
		exit(1);
	}

	string str = "";
	char keyword[20], path[40], temp[20];
	int count, id;
	// Load models
	getline(ifile, str);
	sscanf(str.c_str(), "%s %d", keyword, &count);

	if (strcmp(keyword, "#Models:") != 0)
	{
		printf("ERROR: Invalid File Format - Expected: #Models:");
		return;
	}

	for (int i = 0; i < count; i++)
	{
		getline(ifile, str);
		sscanf(str.c_str(), "%s %d", keyword, &id);
		if (id != i)
		{
			printf("WARNING: modelId is incorrect");
		}

		getline(ifile, str);
		sscanf(str.c_str(), "%s %s", keyword, path);
		
		if (strcmp(keyword, "TERRAIN_FILE") == 0)
		{
			char pathHeightmap[40];
			getline(ifile, str);
			sscanf(str.c_str(), "%s", pathHeightmap);
			Model* model = new Model(path, pathHeightmap);
			m_Models.push_back(model);
		}
		else {
			Model* model = new Model(path);
			m_Models.push_back(model);
		}
	}
	getline(ifile, str);
	// Load textures
	getline(ifile, str);
	sscanf(str.c_str(), "%s %s %d", keyword, temp, &count);

	if (strcmp(keyword, "#2D") != 0)
	{
		printf("ERROR: Invalid File Format - Expected: #2D");
		return;
	}

	for (int i = 0; i < count; i++)
	{
		getline(ifile, str);
		sscanf(str.c_str(), "%s %d", keyword, &id);
		if (id != i)
		{
			printf("WARNING: textureId is incorrect");
		}

		char wrap[20], filterMin[20], filterMag[20];

		getline(ifile, str);
		sscanf(str.c_str(), "%s %s", keyword, path);

		getline(ifile, str);
		sscanf(str.c_str(), "%s %s", keyword, wrap);

		getline(ifile, str);
		sscanf(str.c_str(), "%s %s %s", keyword, filterMin, filterMag);

		Texture* texture = new Texture(path, wrap, filterMin, filterMag);
		m_Textures.push_back(texture);
	}
	getline(ifile, str);
	// Load cube texture
	getline(ifile, str);
	sscanf(str.c_str(), "%s %s %d", keyword, temp, &count);
	if (strcmp(keyword, "#Cube") != 0)
	{
		printf("ERROR: Invalid File Format - Expected: #Cube");
		return;
	}

	for (int i = 0; i < count; i++)
	{
		getline(ifile, str);
		sscanf(str.c_str(), "%s %d", keyword, &id);
		if (id != i)
		{
			printf("WARNING: cubeTextureId is incorrect");
		}

		char wrap[20], filterMin[20], filterMag[20];

		getline(ifile, str);
		sscanf(str.c_str(), "%s %s", keyword, path);

		getline(ifile, str);
		sscanf(str.c_str(), "%s %s", keyword, wrap);

		getline(ifile, str);
		sscanf(str.c_str(), "%s %s %s", keyword, filterMin, filterMag);

		CubeTexture* cubeTexture = new CubeTexture(path, wrap, filterMin, filterMag);
		m_CubeTextures.push_back(cubeTexture);
	}
	getline(ifile, str);
	// Load shaders
	getline(ifile, str);
	sscanf(str.c_str(), "%s %d", keyword, &count);

	if (strcmp(keyword, "#Shaders:") != 0)
	{
		printf("ERROR: Invalid File Format - Expected: #Shaders:");
		exit(1);
	}

	for (int i = 0; i < count; i++)
	{
		getline(ifile, str);
		sscanf(str.c_str(), "%s %d", keyword, &id);
		if (id != i)
		{
			printf("WARNING: shadersId is incorrect");
		}

		char pathFS[40];

		getline(ifile, str);
		sscanf(str.c_str(), "%s %s", keyword, path);

		getline(ifile, str);
		sscanf(str.c_str(), "%s %s", keyword, pathFS);

		Shaders* shaders = new Shaders(path, pathFS);

		int d = 0;
		getline(ifile, str);
		sscanf(str.c_str(), "%s %d", keyword, &d);
		for (int j = 0; j < d; j++)
		{
			int iBool;
			getline(ifile, str);
			sscanf(str.c_str(), "%s %d", keyword, &iBool);
			shaders->SetStates(keyword, iBool);
		}

		m_vShaders.push_back(shaders);
	}
	// Load Sprite
	Sprite* sprite = new Sprite("Textures/Woman2.tga");
	m_Sprite.push_back(sprite);
}

Model* ResourceManager::GetModel(int id)
{
	return m_Models.at(id);
}

Texture* ResourceManager::GetTexture(int id)
{
	return m_Textures.at(id);
}

Shaders* ResourceManager::GetShaders(int id)
{
	return m_vShaders.at(id);
}

CubeTexture* ResourceManager::GetCubeTexture(int id)
{
	return m_CubeTextures.at(id);
}

Sprite* ResourceManager::GetSprite(int id)
{
	return m_Sprite.at(id);
}

ResourceManager::~ResourceManager()
{
	for (auto it = m_Models.begin(); it != m_Models.end(); it++)
	{
		delete (*it);
	}
	m_Models.clear();

	for (auto it = m_Textures.begin(); it != m_Textures.end(); it++)
	{
		delete (*it);
	}
	m_Textures.clear();

	for (auto it = m_CubeTextures.begin(); it != m_CubeTextures.end(); it++)
	{
		delete (*it);
	}
	m_CubeTextures.clear();

	for (auto it = m_vShaders.begin(); it != m_vShaders.end(); it++)
	{
		delete (*it);
	}
	m_vShaders.clear();

	for (auto it = m_Sprite.begin(); it != m_Sprite.end(); it++)
	{
		delete (*it);
	}
	m_Sprite.clear();
}
