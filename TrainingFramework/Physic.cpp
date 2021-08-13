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

Physic::Physic() 
{
	b2Vec2 gravity(0.0f, -10.0f);
	m_world = std::make_unique<b2World>(gravity);
	m_world.get()->SetGravity(b2Vec2(0.0f, -10.0f));

	m_world.get()->SetContactListener(MyContactListener::GetInstance());
}

void Physic::AddBox(Box* box)
{
	m_boxes.push_back(box);
}

b2World* Physic::GetWorld()
{
	return m_world.get();
}

//void Physic::InitBox(vector<GameObject*>& objects) {
//	b2Vec2 gravity(0.0f, -10.0f);
//	m_world = std::make_unique<b2World>(gravity);
//	m_world.get()->SetGravity(b2Vec2(0.0f, -10.0f));
//
//	myContactListenerInstance = new MyContactListener();
//	m_world.get()->SetContactListener(myContactListenerInstance);

	//for (int i = 0; i < objects.size(); i++) {
	//	if (objects[i]->type == GameObject::GROUND || objects[i]->type == GameObject::NONE || objects[i]->type == GameObject::SENSOR) {
	//		GroundBox* grBox = new GroundBox();
	//		grBox->Init(m_world.get(), Vector2(objects[i]->GetPosition().x, objects[i]->GetPosition().y), Vector2(objects[i]->GetDimension().x, objects[i]->GetDimension().y), objects[i]);
	//		m_boxes.push_back(grBox);
	//		m_boxes[i]->SetDynamic(false);
	//	}
	//	else {
	//		DynamicBox* dyBox = new DynamicBox();
	//		dyBox->Init(m_world.get(), Vector2(objects[i]->GetPosition().x, objects[i]->GetPosition().y), Vector2(objects[i]->GetDimension().x, objects[i]->GetDimension().y), objects[i]);
	//		m_boxes.push_back(dyBox);
	//		m_boxes[i]->SetDynamic(true);
	//	}
	//}
//}

//void Physic::Update(float deltaTime, vector<GameObject*>&objects) {
//	m_world.get()->Step(deltaTime, 6, 2);
//
//	for (int i = 0; i < m_boxes.size(); i++) 
//	{
//		if (m_boxes[i]->GetDynmaic()) {
//			DynamicBox* dyBox = (DynamicBox*)m_boxes[i];
//			// add force to player
//			if (jumpPressed && objects[i]->type == GameObject::PLAYER) {
//				dyBox->UpdatePlayer(m_world.get());
//			}
//			dyBox->Update(m_world.get());
//		}
//	}
//	ContactManager::GetInstance()->HandleContact(objects);
//}

void Physic::Update(float deltaTime)
{
	m_world.get()->Step(deltaTime, 6, 2);
	for each (Box * body in m_boxes)
		body->Update();
//	ContactManager::GetInstance()->HandleContact(objects);
}

Physic::~Physic() 
{
	for (int i = 0; i < m_boxes.size(); i++) 
	{
		delete m_boxes[i];
	}
//	delete myContactListenerInstance;
}

