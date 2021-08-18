#include "stdafx.h"
#include "SawBlade.h"

SawBlade::SawBlade()
{
	m_Name = "Saw Blade";
	m_ID = ms_IDMaker;
	ms_IDMaker++;
	m_Collider = NULL;
	m_Time = 0;
	m_angle = 30.0;
	m_rotate = Vector3(0, 0, 1);
}

SawBlade::~SawBlade()
{
}

void SawBlade::CreateCollider()
{
	if (m_Collider == NULL)
	{
		m_Collider = new DynamicBox(this, m_ColliderSize, CATEGORY_SENSOR);
	}
	else
	{
		printf("%s already have a collider", m_Name.c_str());
	}
}

SawBlade* SawBlade::Clone()
{
	SawBlade* copy = new SawBlade();
	copy->m_Transform = m_Transform;
	copy->m_Renderer = m_Renderer->Clone();
	copy->m_ColliderSize = m_ColliderSize;
	return copy;
}

void SawBlade::Draw()
{
	m_Renderer->Draw(m_Transform);
}

void SawBlade::Update(float deltaTime)
{
	m_Time += deltaTime;
	if (m_Time > 0.5)
	{
		m_Transform.rotation += m_rotate * m_angle * PI / 180;
		m_Time = 0;
	}

	m_Renderer->Update(deltaTime);
}