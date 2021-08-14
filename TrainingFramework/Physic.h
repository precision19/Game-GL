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

	vector<Box*> m_boxes;
	unique_ptr<b2World> m_world;
	//MyContactListener* myContactListenerInstance;
public:
	//bool jumpPressed = 0;
	static void CreateInstance();
	static Physic* GetInstance();
	static void DestroyInstance();

	Physic();
	void AddBox(Box*);
	b2World* GetWorld();
	//void InitBox(vector<GameObject*>&);
	//void Update(float deltaTime, vector<GameObject*>&);
	void Update(float deltaTime);
	~Physic();
};

