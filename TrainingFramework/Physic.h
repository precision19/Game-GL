#pragma once
#include <memory>
#include "Box.h"
#include <vector>
#include "MyContactListener.h"

using namespace std;

class Physic
{
private:
	float accumutator;
	static Physic* s_InstancePhysic;
	vector<Box*>m_boxes;
	unique_ptr<b2World> m_world;
public:
	static void CreateInstance();
	static Physic* GetInstance();
	static void DestroyInstance();
	void AddBox(Box* box) { m_boxes.push_back(box); };

	Physic();
	b2World* GetWorld();
	void Update(float deltaTime);
	~Physic();
};

