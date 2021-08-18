#include "stdafx.h"
#include "ContactManager.h"

ContactManager* ContactManager::s_InstanceContact = NULL;

void ContactManager::CreateInstance() 
{
	if (s_InstanceContact == NULL)
		s_InstanceContact = new ContactManager();
}

ContactManager* ContactManager::GetInstance() 
{
	return s_InstanceContact;
}

void ContactManager::DestroyInstance() 
{
	if (s_InstanceContact)
	{
		delete s_InstanceContact;
		s_InstanceContact = NULL;
	}
}

ContactManager::ContactManager()
{
	m_numContacts.clear();
}

ContactManager::~ContactManager()
{
}

void ContactManager::BenginContact(GameObject* obj1, GameObject* obj2)
{
	m_numContacts[{obj1->GetID(), obj2->GetID()}] = 1;
	m_numContacts[{obj2->GetID(), obj1->GetID()}] = 1;
	
	if (m_numContacts[{obj1->GetID(), obj2->GetID()}])
	{
		obj1->OnColliderEnter(obj2);
		obj2->OnColliderEnter(obj1);
	}
}

void ContactManager::EndContact(GameObject* obj1, GameObject* obj2)
{

	if (m_numContacts[{obj2->GetID(), obj1->GetID()}] == 1)
	{
		m_numContacts[{obj1->GetID(), obj2->GetID()}] = 0;
		m_numContacts[{obj2->GetID(), obj1->GetID()}] = 0;
		obj1->OnColliderExit(obj2);
		obj2->OnColliderExit(obj1);
	}
}
//
//void ContactManager::HandleContact(vector<GameObject*>&objects)
//{
//	for (int i = 0; i < objects.size(); i++) 
//	{
//		for (int j = i + 1; j < objects.size(); j++) 
//		{
//			if (m_numContacts[{objects[i]->GetID(), objects[j]->GetID()}]) 
//			{
//				printf("Collision of Object %d and Object %d\n", objects[i]->GetID(), objects[j]->GetID());
//			}
//		}
//	}
//}


