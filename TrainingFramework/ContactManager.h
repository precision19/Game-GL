#pragma once
#include "GameObject.h"
using namespace std;

class ContactManager
{
private:
	map<pair<int, int>, int>m_numContacts;
	static ContactManager* s_InstanceContact;
public:
	ContactManager();
	~ContactManager();
	static void CreateInstance();
	static ContactManager* GetInstance();
	static void DestroyInstance();
	void BenginContact(GameObject*, GameObject*);
	void EndContact(GameObject*, GameObject*);
	/*void HandleContact(vector<GameObject*>&m_vObject);*/
};

