#pragma once
#include <memory>
#include "Box.h"
#include <vector>
#include "MyContactListener.h"

using namespace std;

class Physic
{
private:
	static Physic* s_InstancePhysic;

	unique_ptr<b2World> m_world;
public:
	static void CreateInstance();
	static Physic* GetInstance();
	static void DestroyInstance();

	Physic();
	b2World* GetWorld();
	void Update(float deltaTime);
	~Physic();
};

