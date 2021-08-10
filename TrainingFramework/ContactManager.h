#pragma once
#include <map>
#include "Object.h"
using namespace std;
class ContactManager
{
private:
	map<pair<int, int>, int>m_numContacts;
	static ContactManager* s_InstanceContact;
public:
	ContactManager();
	~ContactManager();
	static ContactManager* GetInstance();
	static void CreateInstance();
	static void DestroyInstance();
	void BenginContact(Object*, Object*);
	void EndContact(Object*, Object*);
	void HandleContact(vector<Object*>&m_vObject);
};

