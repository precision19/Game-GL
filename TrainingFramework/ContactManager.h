#pragma once
#include "GameObject.h"
using namespace std;

class GameObject;
class ContactManager
{
private:
	map<pair<int, int>, bool>m_numContacts;
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

