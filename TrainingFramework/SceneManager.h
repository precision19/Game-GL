#pragma once
#include <vector>
#include "Object.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "box2d/box2d.h"
#include "Box.h"

class SceneManager
{
protected:
	static SceneManager* ms_Instance;

	ResourceManager* m_Resource;
	std::vector<Box>m_boxes;
public:
	vector<Object*> m_vObjects;
	std::unique_ptr<b2World>m_world;
	SceneManager(const char*);
	SceneManager(string);
	void Init(const char*);
	void Draw();
	void Update(float);
	~SceneManager();
};

