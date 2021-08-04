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
	static ResourceManager* ms_Instance;

	vector<Model*> m_Models;
	vector<Texture*> m_Textures;
	vector<CubeTexture*> m_CubeTextures;
	vector<Shaders*> m_vShaders;

	Model* m_SpriteModel;
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
	Model* GetSpriteModel();

	void DeleteAllResources();
	~ResourceManager();
};

