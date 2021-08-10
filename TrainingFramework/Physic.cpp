#include "stdafx.h"
#include "Physic.h"

Physic* Physic::s_InstancePhysic = NULL;

void Physic::CreateInstance() {
	if (s_InstancePhysic == NULL) {
		s_InstancePhysic = new Physic();
	}
}

void Physic::DestroyInstance() {
	if (s_InstancePhysic) {
		delete s_InstancePhysic;
		s_InstancePhysic = NULL;
	}
}

Physic* Physic::GetInstance() {
	return s_InstancePhysic;
}

Physic::Physic() {
	
}

void Physic::InitBox(vector<Object*>& m_vObjects) {
	b2Vec2 gravity(0.0f, -10.0f);
	m_world = std::make_unique<b2World>(gravity);
	m_world.get()->SetGravity(b2Vec2(0.0f, -10.0f));

	myContactListenerInstance = new MyContactListener();
	m_world.get()->SetContactListener(myContactListenerInstance);

	for (int i = 0; i < SceneManager::GetInstance()->m_vObjects.size(); i++) {
		if (strncmp(SceneManager::GetInstance()->m_vObjects[i]->type, "GROUND", 6) == 0) {
			GroundBox* grBox = new GroundBox();
			grBox->Init(m_world.get(), Vector2(m_vObjects[i]->GetPosition().x, m_vObjects[i]->GetPosition().y), Vector2(m_vObjects[i]->GetDimension().x, m_vObjects[i]->GetDimension().y), m_vObjects[i]);
			m_boxes.push_back(grBox);
			m_boxes[i]->SetDynamic(false);
		}
		else {
			DynamicBox* dyBox = new DynamicBox();
			dyBox->Init(m_world.get(), Vector2(m_vObjects[i]->GetPosition().x, m_vObjects[i]->GetPosition().y), Vector2(m_vObjects[i]->GetDimension().x, m_vObjects[i]->GetDimension().y), m_vObjects[i]);
			/*dyBox->setObj(m_vObjects[i]);*/
			m_boxes.push_back(dyBox);
			m_boxes[i]->SetDynamic(true);
		}
	}
}

void Physic::Update(float deltaTime, vector<Object*>&m_vObjects) {
	m_world.get()->Step(deltaTime, 6, 2);

	for (int i = 0; i < m_boxes.size(); i++) 
	{
		if (m_boxes[i]->GetDynmaic()) {
			DynamicBox* dyBox = (DynamicBox*)m_boxes[i];
			// add force to player
			if (jumpPressed && strncmp(m_vObjects[i]->type, "PLAYER", 6) == 0 ) {
				dyBox->UpdatePlayer(m_world.get());
			}
			dyBox->Update(m_world.get());
		}
	}

	ContactManager::GetInstance()->HandleContact(m_vObjects);
}

Physic::~Physic() {
	for (int i = 0; i < m_boxes.size(); i++) {
		delete m_boxes[i];
	}
	delete myContactListenerInstance;
}

