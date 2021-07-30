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
	ResourceManager* m_Resource;
	Camera* m_Camera;
	std::vector<Object*> m_spObjects;
public:
	static void CreateInstance();
	static SceneManager* GetInstance();
	static void DestroyInstance();

	SceneManager();
	SceneManager(const char*);
	void Init(const char*);
	int Init();
	void Draw();
	void Update(float);
	~SceneManager();
};

