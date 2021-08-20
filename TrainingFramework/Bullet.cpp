#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{
	m_time = 0;
	m_Name = "Bullet";
	m_ID = ms_IDMaker;
	ms_IDMaker++;
	m_Collider = NULL;
//	m_speed = 0;
}

Bullet::~Bullet()
{
}

Bullet* Bullet::Clone()
{
	Bullet* copy = new Bullet();
	copy->m_Transform = m_Transform;
	copy->m_Renderer = m_Renderer->Clone();
	copy->m_ColliderSize = m_ColliderSize;
	copy->m_speed = m_speed;
	return copy;
}

void Bullet::SetSpeed(float speed)
{
	m_speed = speed;
}

void Bullet::CreateCollider()
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

void Bullet::Update(float deltaTime)
{
	m_time += deltaTime;
	if (m_time > 0.1)
	{
		m_Transform.position.y -= m_speed;
		m_time = 0;
	}

	if (m_Transform.position.y == -200)
	{
		m_Transform.position.y += 400;
	}
	m_Renderer->Update(deltaTime);


}
