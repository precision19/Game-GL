#pragma once
#include "ContactManager.h"

class MyContactListener : public b2ContactListener
{
protected:
	static MyContactListener* ms_Instance;
public:
	static void CreateInstance();
	static void DestroyInstance();
	static MyContactListener* GetInstance();
	MyContactListener();

	void BeginContact(b2Contact*);
	void EndContact(b2Contact*);

	~MyContactListener();
};

