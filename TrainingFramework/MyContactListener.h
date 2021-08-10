#pragma once
#include "box2d/box2d.h"
#include "DynamicBox.h"
class MyContactListener:public b2ContactListener
{
public:
	void BeginContact(b2Contact*);
	void EndContact(b2Contact*);
	MyContactListener();
	~MyContactListener();
};

