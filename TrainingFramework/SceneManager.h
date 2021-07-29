#pragma once
#include <vector>
#include "Object.h"
#include "Camera.h"
#include "ResourceManager.h"

class SceneManager
{
protected:
	static SceneManager* ms_Instance;
	vector<Object*> m_vObjects;
public:
	static void CreateInstance();
	static SceneManager* GetInstance();
	static void DestroyInstance();

	SceneManager();
	int Init();
	void Draw();
	void Update(float);
	~SceneManager();
};

