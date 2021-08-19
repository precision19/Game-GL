#include "stdafx.h"
#include "Guard.h"

Guard::Guard()
{
	m_time = 0;
	m_Name = "Bullet";
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
		m_Collider = new DynamicBox(this, m_ColliderSize, CATEGORY_NOTGRAVITY);
	}
	else
	{
		printf("%s already have a collider", m_Name.c_str());
	}
}

void Guard::Update(float deltaTime)
{
	DynamicBox* db = (DynamicBox*)m_Collider;
	SetPosition(Vector3(db->getBody()->GetPosition().x, db->getBody()->GetPosition().y, GetPosition().z));

	if (db->getBody()->GetPosition().x > (m_positionStart.x - m_error * 2 ) && db->getBody()->GetPosition().x < (m_positionStart.x + m_error * 2) && vectorX == true )
	{
		boolX = true;
		m_Transform.rotation += m_rotate * PI;
		vectorX = false;
	}
	else if (db->getBody()->GetPosition().x > (m_positionEnd.x - m_error * 2) && db->getBody()->GetPosition().x < (m_positionEnd.x + m_error * 2) && vectorX == false)
	{
		boolX = false;
		m_Transform.rotation += m_rotate * PI;
		vectorX = true;
	}

	if (boolX)
	{
		db->SetVelocity(Vector2(m_speed, db->GetVelocity().y));
	}
	else
	{
		db->SetVelocity(Vector2(-m_speed, db->GetVelocity().y));
	}
	m_Renderer->Update(deltaTime);
}

Guard::~Guard()
{
}
