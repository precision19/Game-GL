#pragma once
#include <vector>
#include "Object.h"
#include "Camera.h"
#include "ResourceManager.h"

class SceneManager
{
protected:
	static SceneManager* ms_Instance;

	ResourceManager* m_Resource;
public:
	vector<Object*> m_vObjects;

	SceneManager(const char*);
	SceneManager(string);
	void Init(const char*);
	void Draw();
	void Update(float);
	~SceneManager();
};

