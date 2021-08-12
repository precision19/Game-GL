#include "stdafx.h"
#include "ContactManager.h"

ContactManager* ContactManager::s_InstanceContact = NULL;

ContactManager::ContactManager(){
	m_numContacts.clear();
}
ContactManager::~ContactManager(){}
void ContactManager::CreateInstance() {
	if (s_InstanceContact == NULL)
		s_InstanceContact = new ContactManager();
}

void ContactManager::DestroyInstance() {
	if (s_InstanceContact)
	{
		delete s_InstanceContact;
		s_InstanceContact = NULL;
	}
}

ContactManager* ContactManager::GetInstance() {
	return s_InstanceContact;
}

void ContactManager::BenginContact(Object* obj1, Object* obj2) {
	if (m_numContacts[{obj1->GetID(), obj2->GetID()}] < INT_MAX) {
		m_numContacts[{obj1->GetID(), obj2->GetID()}]++;
	}
	if (m_numContacts[{obj2->GetID(), obj1->GetID()}] < INT_MAX) {
		m_numContacts[{obj2->GetID(), obj1->GetID()}]++;
	}
}

void ContactManager::EndContact(Object* obj1, Object* obj2) {
	m_numContacts[{obj1->GetID(), obj2->GetID()}]--;
	m_numContacts[{obj2->GetID(), obj1->GetID()}]--;
}

void ContactManager::HandleContact(vector<Object*>&m_vObject) {
	for (int i = 0; i < m_vObject.size(); i++) {
		for (int j = i + 1; j < m_vObject.size(); j++) {
			if (m_numContacts[{m_vObject[i]->GetID(), m_vObject[j]->GetID()}]) {
				printf("Collision of Object %d and Object %d\n", m_vObject[i]->GetID(), m_vObject[j]->GetID());
			}
		}
	}
}


