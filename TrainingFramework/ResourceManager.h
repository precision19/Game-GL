#pragma once
#include <vector>
#include "Shaders.h"
#include "Model.h"
#include "Texture.h"
#include "CubeTexture.h"
#include "Helper.h"

class ResourceManager
{
protected:
	vector<Model*> m_Models;
	vector<Texture*> m_Textures;
	vector<CubeTexture*> m_CubeTextures;
	vector<Shaders*> m_vShaders;
public:

	ResourceManager();
	ResourceManager(const char*);
	~ResourceManager();

	Model* GetModel(int);
	Texture* GetTexture(int);
	Shaders* GetShaders(int);
	CubeTexture* GetCubeTexture(int);
};

