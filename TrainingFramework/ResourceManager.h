#pragma once
#include "EventManager.h"
#include <vector>
#include "Shaders.h"
#include "Model.h"
#include "CubeTexture.h"

class ResourceManager
{
protected:
	static ResourceManager* ms_Instance;

	vector<Model*> m_Models;
	vector<Texture*> m_Textures;
	vector<CubeTexture*> m_CubeTextures;
	vector<Shaders*> m_vShaders;
public:
	static void CreateInstance();
	static ResourceManager* GetInstance();
	static void DestroyInstance();

	ResourceManager();

	void LoadResource(string);

	Model* GetModel(int);
	Model* GetModel(string);
	Texture* GetTexture(int);
	Texture* GetTexture(string);
	Shaders* GetShaders(int);
	Shaders* GetShaders(string);
	CubeTexture* GetCubeTexture(int);

	void DeleteAllResources();
	~ResourceManager();
};

