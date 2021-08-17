#include "stdafx.h"
#include "Sensor.h"
#include "GroundBox.h"

Sensor::Sensor(Pos pos) {
	m_Name = "Sensor";
	m_ID = ms_IDMaker;
	ms_IDMaker++;
	m_Collider = NULL;
	this->pos = pos;
	numContact = 0;
}

Sensor::~Sensor() {
	m_Renderer = NULL;
	m_Collider = NULL;
}

void Sensor::CreateCollider()
{
	if (m_Collider == NULL)
	{
		if (pos != OTHER) {
			m_Collider = new DynamicBox(this, m_ColliderSize, CATEGORY_SENSOR_PLAYER);
			Physic::GetInstance()->AddBox(m_Collider);
		}
		else {
			m_Collider = new GroundBox(this, Vector2(m_ColliderSize, m_ColliderSize), CATEGORY_SENSOR);
		}
	}
	else
	{
		printf("%s already has a collider", m_Name.c_str());
	}
}

void Sensor::Update(float deltaTime) {

}

void Sensor::OnColliderEnter(GameObject* other) {
	if (other->GetName() == "Block") {
		numContact++;
	}
}

void Sensor::OnColliderExit(GameObject* other) {
	if (other->GetName() == "Block") {
		numContact--;
	}
}