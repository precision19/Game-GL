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
	m_boxes.clear();
	b2Vec2 gravity(0.0f, -10.0f);
	m_world = std::make_unique<b2World>(gravity);
	m_world.get()->SetGravity(b2Vec2(0.0f, -100.0f));
	accumutator = 0.0f;

	m_world.get()->SetContactListener(MyContactListener::GetInstance());
}

b2World* Physic::GetWorld()
{
	return m_world.get();
}


void Physic::Update(float deltaTime)
{
	accumutator += deltaTime;
	while (accumutator > 1.0f / 60) {
		accumutator -= 1.0f / 60;
		m_world.get()->Step(1.0f / 60, 6, 2);
	}
}

Physic::~Physic() 
{
	for (int i = 0; i < m_boxes.size(); i++) {
		delete m_boxes[i];
		m_boxes[i] = NULL;
	}
}

