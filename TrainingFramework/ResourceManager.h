#pragma once
#include <vector>
#include "Shaders.h"
#include "Model.h"
#include "Texture.h"
#include "CubeTexture.h"

class ResourceManager
{
protected:
	vector<Model*> m_Models;
	vector<Texture*> m_Textures;
	vector<CubeTexture*> m_CubeTextures;
	vector<Shaders*> m_vShaders;

	static ResourceManager* ms_Instance;
public:
	static void CreateInstance();
	static ResourceManager* GetInstance();
	static void DestroyInstance();

	ResourceManager();
	~ResourceManager();

	Model* GetModel(int);
	Texture* GetTexture(int);
	Shaders* GetShaders(int);
	CubeTexture* GetCubeTexture(int);
};

