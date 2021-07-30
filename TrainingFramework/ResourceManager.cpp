#include "stdafx.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager(const char* filePath)
{
	FILE* f = fopen(filePath, "r+");

	if (f == NULL)
	{
		printf("Invalid file %s\n", filePath);
		exit(1);
	}

	int amount;
	char keyword[30], path[40];
	fscanf(f, "#Models: %d\n", &amount);
	for (int i = 0; i < amount; i++)
	{
		int id;
		fscanf(f, "ID %d\n", &id);
		if (id != i)
			printf("WARNING: model's ID is not correct\n");

		fscanf(f, "%s %s\n", keyword, path);

		if (strcmp(keyword, "TERRAIN_FILE") == 0)
		{
			char path2[30];
			fscanf(f, "%s\n", path2);
			Model* model = new Model(path, path2);
			m_Models.push_back(model);
		}
		else {
			Model* model = new Model(path);
			m_Models.push_back(model);
		}
	}

	fscanf(f, "#Textures: %d\n", &amount);
	for (int i = 0; i < amount; i++)
	{
		int id;
		fscanf(f, "ID %d\n", &id);
		if (id != i)
			printf("WARNING: Texture's ID is not correct\n");

		char wrap[20], filterMin[20], filterMag[20];
		fscanf(f, "FILE %s\n", path);
		fscanf(f, "WRAP %s\n", wrap);
		fscanf(f, "FILTER %s %s\n", filterMin, filterMag);
		Texture* texture = new Texture(path, wrap, filterMin, filterMag);
		m_Textures.push_back(texture);
	}

	fscanf(f, "#CubeTextures: %d\n", &amount);
	for (int i = 0; i < amount; i++)
	{
		int id;
		fscanf(f, "ID %d\n", &id);
		if (id != i)
			printf("WARNING: CubeTexture's ID is not correct\n");

		char wrap[20], filterMin[20], filterMag[20];
		fscanf(f, "FILE %s\n", path);
		fscanf(f, "WRAP %s\n", wrap);
		fscanf(f, "FILTER %s %s\n", filterMin, filterMag);
		CubeTexture* texture = new CubeTexture(path, wrap, filterMin, filterMag);
		m_CubeTextures.push_back(texture);
	}

	fscanf(f, "#Shaders: %d\n", &amount);
	for (int i = 0; i < amount; i++)
	{
		int id;
		fscanf(f, "ID %d\n", &id);
		if (id != i)
			printf("WARNING: Shader's ID is not correct\n");

		char vs[30], fs[30];
		fscanf(f, "VS %s\n", vs);
		fscanf(f, "FS %s\n", fs);
		Shaders* shaders = new Shaders(vs, fs);

		int stateAmount;
		fscanf(f, "STATES %d\n", &stateAmount);
		for (int j = 0; j < stateAmount; j++)
		{
			int iBool;
			fscanf(f, "%s %d\n", keyword, &iBool);
			shaders->SetStates(keyword, iBool);
		}

		m_vShaders.push_back(shaders);
	}

	fclose(f);

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
}
