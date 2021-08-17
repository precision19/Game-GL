#include "stdafx.h"
#include "Gun.h"
#include "GroundBox.h"

Gun::Gun()
{
	m_Timer = 0;
	m_Name = "Gun";
	m_ID = ms_IDMaker;
	ms_IDMaker++;
	m_Collider = NULL;
	m_Timer = 0;
	m_Cooldown = 1;
}

GameObject* Gun::Clone()
{
	Gun* copy = new Gun();
	copy->m_Transform = m_Transform;
	copy->m_Renderer = m_Renderer->Clone();
	return copy;
}

void Gun::Update(float deltaTime)
{	
	m_Timer += deltaTime;
	if (m_Timer > m_Cooldown)
	{	
		m_Timer = 0;
		printf("Fire");
	}

	m_Renderer->Update(deltaTime);
}

Gun::~Gun()
{
	
}
