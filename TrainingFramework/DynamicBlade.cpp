#include "stdafx.h"
#include "DynamicBlade.h"

DynamicBlade::DynamicBlade()
{
	m_Name = DYNAMIC_BLADE;
	m_ID = ms_IDMaker;
	ms_IDMaker++;
	m_Collider = NULL;
	m_rotate = Vector3(0, 0, 1);
	vectorY = false;
}

DynamicBlade* DynamicBlade::Clone()
{
	DynamicBlade* copy = new DynamicBlade();
	copy->m_Transform = m_Transform;
	copy->m_Renderer = m_Renderer->Clone();
	copy->m_ColliderSize = m_ColliderSize;
	copy->m_speed = m_speed;
	return copy;
}

void DynamicBlade::SetPositionStart(Vector3 start)
{
	m_positionStart = start;
}

void DynamicBlade::SetPositionEnd(Vector3 end)
{
	m_positionEnd = end;
}

void DynamicBlade::SetSpeed(float speed)
{
	m_speed = speed;
}

void DynamicBlade::CreateCollider()
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

void DynamicBlade::Update(float deltaTime)
{
	SetPosition(Vector3(m_Collider->getBody()->GetPosition().x, m_Collider->getBody()->GetPosition().y, GetPosition().z));
	m_Transform.rotation += m_rotate * 3 * PI / 180;
	if (m_positionStart.y < m_positionEnd.y)
	{
		if (m_Collider->getBody()->GetPosition().y < m_positionStart.y && vectorY == true)
		{
			boolY = true;
			vectorY = false;
		}
		else if (m_Collider->getBody()->GetPosition().y > m_positionEnd.y && vectorY == false)
		{
			boolY = false;
			vectorY = true;
		}
		if (boolY)
		{
			m_Collider->SetVelocity(Vector2(m_Collider->GetVelocity().x, m_speed));
		}
		else
		{
			m_Collider->SetVelocity(Vector2(m_Collider->GetVelocity().x, -m_speed));
		}
	}
	else
	{
		if (m_Collider->getBody()->GetPosition().y < m_positionEnd.y && vectorY == true)
		{
			boolY = true;
			vectorY = false;
		}
		else if (m_Collider->getBody()->GetPosition().y > m_positionStart.y && vectorY == false)
		{
			boolY = false;
			vectorY = true;
		}
		if (boolY)
		{
			m_Collider->SetVelocity(Vector2(m_Collider->GetVelocity().x, m_speed));
		}
		else
		{
			m_Collider->SetVelocity(Vector2(m_Collider->GetVelocity().x, -m_speed));
		}
	}
	
	m_Renderer->Update(deltaTime);
}

DynamicBlade::~DynamicBlade()
{
}
