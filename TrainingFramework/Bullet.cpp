#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{
	m_IsRender = false;
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

void Bullet::Draw() {
	if (m_IsRender) {
		m_Renderer->Draw(m_Transform);
	}
}

void Bullet::Update(float deltaTime)
{
	if (m_IsRender) {
		m_Collider->SetVelocity(Vector2(m_speed * m_VectorSpeed.x, m_speed * m_VectorSpeed.y));
		SetPosition(Vector3(m_Collider->getBody()->GetPosition().x, m_Collider->getBody()->GetPosition().y, GetPosition().z));
		m_Renderer->Update(deltaTime);
	}
}

void Bullet::OnColliderEnter(GameObject* other)
{
	if (other->GetName() == "Block") {
		m_IsRender = false;
	}
}

void Bullet::OnColliderExit(GameObject* other)
{
	
}
