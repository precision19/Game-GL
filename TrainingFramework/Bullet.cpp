#include "stdafx.h"
#include "Bullet.h"
#include "GroundBox.h"

Bullet::Bullet()
{
	m_Name = "Bullet";
	m_ID = ms_IDMaker;
	ms_IDMaker++;
	m_Collider = NULL;
	m_speed = 1;
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
		m_Collider = new DynamicBox(this, m_ColliderSize, CATEGORY_NOTGRAVITY);
		((DynamicBox*)m_Collider)->SetVelocity(Vector2(m_speed, 0));
	}
	else
	{
		printf("%s already have a collider", m_Name.c_str());
	}
}

void Bullet::Update(float deltaTime)
{
	if (!m_IsActive) return;

	Vector2 newPosition = ((DynamicBox*)m_Collider)->GetPosition();
	m_Transform.position.x = newPosition.x;
	m_Transform.position.y = newPosition.y;
	m_Renderer->Update(deltaTime);
}

void Bullet::OnColliderEnter(GameObject*)
{
	printf("Disable bullet");
}

