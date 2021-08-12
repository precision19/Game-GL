#pragma once
#include "Animation2D.h"

class PrefabManager
{
protected:
	static PrefabManager* ms_Instance;
	vector<Renderer*> m_Renderers;
public:
	static void CreateInstance();
	static PrefabManager* GetInstance();
	static void DestroyInstance();

	PrefabManager();
	void LoadPrefabs(string);
	Renderer* GetRenderer(int);
	void DestroyAllPrefab();
	~PrefabManager();
};

