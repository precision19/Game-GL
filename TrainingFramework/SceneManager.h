#pragma once
#include <vector>
#include "Object.h"
#include "Camera.h"
#include "ResourceManager.h"

class SceneManager
{
protected:
	static SceneManager* ms_Instance;
	vector<Object*> m_spObjects;
	ResourceManager* m_Resource;
	Camera* m_Camera;
public:
	vector<Object*> m_vObjects;
	SceneManager(const char*);
	void Init(const char*);
	void Draw();
	void Update(float);
	~SceneManager();
};

