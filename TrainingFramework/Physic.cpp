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
	m_world.get()->SetGravity(b2Vec2(0.0f, -100.0f));

	m_world.get()->SetContactListener(MyContactListener::GetInstance());
}


b2World* Physic::GetWorld()
{
	return m_world.get();
}


void Physic::Update(float deltaTime)
{
	m_world.get()->Step(deltaTime, 6, 2);
}

Physic::~Physic() 
{

}

