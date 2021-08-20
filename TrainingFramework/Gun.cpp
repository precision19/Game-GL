#include "stdafx.h"
#include "Gun.h"

Gun::Gun()
{
	m_time = 0;
	m_Name = "Gun";
	m_ID = ms_IDMaker;
	ms_IDMaker++;
	m_Collider = NULL;
}

Gun* Gun::Clone()
{
	Gun* copy = new Gun();
	copy->m_Transform = m_Transform;
	copy->m_Renderer = m_Renderer->Clone();
	copy->m_ColliderSize = m_ColliderSize;
	return copy;
}

void Gun::CreateCollider()
{
	if (m_Collider == NULL)
	{
		m_Collider = new Box(this, m_ColliderSize, CATEGORY_SENSOR, true, "Circle");
	}
	else
	{
		printf("%s already have a collider", m_Name.c_str());
	}
}

void Gun::Update(float deltaTime)
{	
	m_time += deltaTime;
	if (m_time > 0.4)
	{	
		m_time = 0;
	}

	m_Renderer->Update(deltaTime);
}

void Gun::Draw()
{
	m_Renderer->Draw(m_Transform);
}

Gun::~Gun()
{

}
