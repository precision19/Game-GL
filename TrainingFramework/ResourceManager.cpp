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
	char keyword[30], name[40];
	fscanf(f, "#Models: %d\n", &amount);
	for (int i = 0; i < amount; i++)
	{
		fscanf(f, "%s %s\n", keyword, name);
		Model* model = new Model(name, strcmp(keyword, "TERRAIN") == 0);
		if (strcmp(name, "Sprite") == 0)
			m_SpriteModel = model;
		m_Models.push_back(model);
	}

	fscanf(f, "#2DTextures: %d\n", &amount);
	for (int i = 0; i < amount; i++)
	{
		char wrap[20], filterMin[20], filterMag[20];
		fscanf(f, "%s %s %s\t%s\n", wrap, filterMin, filterMag, name);
		Texture* texture = new Texture(name, wrap, filterMin, filterMag);
		m_Textures.push_back(texture);
	}

	fscanf(f, "#CubeTextures: %d\n", &amount);
	for (int i = 0; i < amount; i++)
	{
		char wrap[20], filterMin[20], filterMag[20];
		fscanf(f, "%s %s %s\t%s\n", wrap, filterMin, filterMag, name);
		string path = "Textures/" + string(name);
		CubeTexture* texture = new CubeTexture(path.c_str(), wrap, filterMin, filterMag);
		m_CubeTextures.push_back(texture);
	}

	fscanf(f, "#Shaders: %d\n", &amount);
	for (int i = 0; i < amount; i++)
	{
		int stateAmount;
		fscanf(f, "NAME %s - %d STATE(S)", name, &stateAmount);
		string pathVS = "Shaders/" + string(name) + ".vs";
		string pathFS = "Shaders/" + string(name) + ".fs";
		Shaders* shaders = new Shaders((char*)pathVS.c_str(), (char*)pathFS.c_str());

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

Model* ResourceManager::GetModel(string name)
{
	for (int i = 0; i < m_Models.size(); i++)
		if (name == m_Models.at(i)->GetName())
			return m_Models.at(i);
	printf("WARNING: Can't find model %s\n", name.c_str());
	return NULL;
}

Texture* ResourceManager::GetTexture(int id)
{
	return m_Textures.at(id);
}

Texture* ResourceManager::GetTexture(string name)
{
	for (int i = 0; i < m_Textures.size(); i++)
		if (name == m_Textures.at(i)->GetName())
			return m_Textures.at(i);
	printf("WARNING: Can't find texture %s\n", name.c_str());
	return NULL;
}

Shaders* ResourceManager::GetShaders(int id)
{
	return m_vShaders.at(id);
}

CubeTexture* ResourceManager::GetCubeTexture(int id)
{
	return m_CubeTextures.at(id);
}

Model* ResourceManager::GetSpriteModel()
{
	return m_SpriteModel;
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
