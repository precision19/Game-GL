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
	vector<Object*> m_spObjects;
	ResourceManager* m_Resource;
	Camera* m_Camera;
	std::vector<Box>m_boxes;
public:
	std::unique_ptr<b2World>m_world;
	vector<Object*> m_vObjects;
	SceneManager(const char*);
	void Init(const char*);
	void Draw();
	void Update(float);
	~SceneManager();
};

