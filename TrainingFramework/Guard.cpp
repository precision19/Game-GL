#include "stdafx.h"
#include "Guard.h"

Guard::Guard()
{
	m_time = 0;
	m_Name = "Guard";
	m_ID = ms_IDMaker;
	ms_IDMaker++;
	m_Collider = NULL;
	m_rotate = Vector3(0, 1, 0);
	vectorX = false;
}

Guard* Guard::Clone()
{
	Guard* copy = new Guard();
	copy->m_Transform = m_Transform;
	copy->m_Renderer = m_Renderer->Clone();
	copy->m_ColliderSize = m_ColliderSize;
	copy->m_speed = m_speed;
	return copy;
}

void Guard::SetPositionStart(Vector3 start)
{
	m_positionStart = start;
}

void Guard::SetPositionEnd(Vector3 end)
{
	m_positionEnd = end;
}

void Guard::SetSpeed(float speed)
{
	m_speed = speed;
	m_error = speed / 100;
}

void Guard::CreateCollider()
{
	if (m_Collider == NULL)
	{
		m_Collider = new Box(this, m_ColliderSize, CATEGORY_NOTGRAVITY, true, "Circle");
	}
	else
	{
		printf("%s already have a collider", m_Name.c_str());
	}
}

void Guard::Update(float deltaTime)
{
	SetPosition(Vector3(m_Collider->getBody()->GetPosition().x, m_Collider->getBody()->GetPosition().y, GetPosition().z));

	if (m_Collider->getBody()->GetPosition().x > (m_positionStart.x - m_error * 2 ) && m_Collider->getBody()->GetPosition().x < (m_positionStart.x + m_error * 2) && vectorX == true )
	{
		boolX = true;
		m_Transform.rotation += m_rotate * PI;
		vectorX = false;
	}
	else if (m_Collider->getBody()->GetPosition().x > (m_positionEnd.x - m_error * 2) && m_Collider->getBody()->GetPosition().x < (m_positionEnd.x + m_error * 2) && vectorX == false)
	{
		boolX = false;
		m_Transform.rotation += m_rotate * PI;
		vectorX = true;
	}

	if (boolX)
	{
		m_Collider->SetVelocity(Vector2(m_speed, m_Collider->GetVelocity().y));
	}
	else
	{
		m_Collider->SetVelocity(Vector2(-m_speed, m_Collider->GetVelocity().y));
	}
	m_Renderer->Update(deltaTime);
}

Guard::~Guard()
{
}
