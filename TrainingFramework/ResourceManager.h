#pragma once
#include <vector>
#include "Shaders.h"
#include "Model.h"
#include "Texture.h"
#include "CubeTexture.h"
#include "Helper.h"
#include "Sprite.h"

class ResourceManager
{
protected:
	vector<Model*> m_Models;
	vector<Texture*> m_Textures;
	vector<CubeTexture*> m_CubeTextures;
	vector<Shaders*> m_vShaders;

	Model* m_SpriteModel;
public:

	ResourceManager();
	ResourceManager(const char*);
	~ResourceManager();

	Model* GetModel(int);
	Model* GetModel(string);
	Texture* GetTexture(int);
	Texture* GetTexture(string);
	Shaders* GetShaders(int);
	Shaders* GetShaders(string);
	CubeTexture* GetCubeTexture(int);

	Model* GetSpriteModel();
};

