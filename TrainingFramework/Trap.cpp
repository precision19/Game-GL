#include "stdafx.h"
#include "Trap.h"

Trap::Trap()
{
	currentAnim = 0;
	m_angle = 30.0;
	m_rotate = Vector3(0, 0, 1);
	m_Frame = 0;
}

Trap::~Trap()
{

}

Trap* Trap::Clone()
{
	Trap* result = new Trap();

	result->m_Name = m_Name;
	result->m_Dimension = m_Dimension;
	result->m_Transform = m_Transform;
	result->m_Renderer = m_Renderer->Clone();

	return result;
}

void Trap::Draw()
{
	m_Renderer->Draw(m_Transform);
}

void Trap::Update(float deltaTime)
{
	m_Frame += deltaTime;
	if (m_Frame > 0.5)
	{
		m_Transform.rotation += m_rotate * m_angle * PI / 180;
		m_Frame = 0;
	}

	m_Renderer->Update(deltaTime);
}
