#pragma once
#include "box2d/box2d.h"
#include <memory>
#include "MyContactListener.h"
#include "Box.h"
#include "GroundBox.h"
#include "DynamicBox.h"
#include "SceneManager.h"

class Physic
{
private:
	static Physic* s_InstancePhysic;
	std::unique_ptr<b2World>m_world;
	MyContactListener* myContactListenerInstance;
	std::vector<Box*>m_boxes;
public:
	bool jumpPressed = 0;
	Physic();
	~Physic();
	static void CreateInstance();
	static void DestroyInstance();
	static Physic* GetInstance();
	void InitBox(vector<Object*>& m_vObejcts);
	void Update(float deltaTime, vector<Object*>&m_vObjects);
};

