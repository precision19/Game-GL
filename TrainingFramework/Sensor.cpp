#include "stdafx.h"
#include "Sensor.h"

Sensor::Sensor(Pos pos) {
	m_Name = "Sensor";
	m_ID = ms_IDMaker;
	ms_IDMaker++;
	m_Collider = NULL;
	this->pos = pos;
}

Sensor::~Sensor() {

}

void Sensor::CreateCollider()
{
	if (m_Collider == NULL)
	{
		m_Collider = new DynamicBox(this, m_ColliderSize, CATEGORY_SENSOR);
	}
	else
	{
		printf("%s already has a collider", m_Name.c_str());
	}
}

void Sensor::Update(float deltaTime) {

}