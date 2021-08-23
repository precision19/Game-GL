#include "stdafx.h"
#include "SpinnerFly.h"

SpinnerFly::SpinnerFly()
{
	m_Time = 0;
	m_Name = SPINNER;
	m_ID = ms_IDMaker;
	ms_IDMaker++;
	m_Collider = NULL;
	m_angle = 0;
	m_rotate = Vector3(0, 1, 0);
	vectorX = false;
}

SpinnerFly* SpinnerFly::Clone()
{
	SpinnerFly* copy = new SpinnerFly();
	copy->m_Transform = m_Transform;
	copy->m_Renderer = m_Renderer->Clone();
	copy->m_ColliderSize = m_ColliderSize;
	copy->m_speed = m_speed;
	return copy;
}

void SpinnerFly::SetSpeed(float speed)
{
	m_speed = speed;
}

void SpinnerFly::SetPositionCenter(Vector3 center)
{
	m_positionCenter = center;
}

void SpinnerFly::SetRadius()
{
	Vector3 vR;
	vR = m_Transform.position - m_positionCenter;
	m_radius = vR.Length();
}

void SpinnerFly::CreateCollider()
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

void SpinnerFly::Update(float deltaTime)
{
	SetPosition(Vector3(m_Collider->getBody()->GetPosition().x, m_Collider->getBody()->GetPosition().y, GetPosition().z));

	if (m_angle > 2 * PI)
	{
		m_angle = 0;
	}

	m_Time += deltaTime;
	if (m_Time >= 0.07)
	{
		m_angle += m_speed;
		m_Time = 0;
	}

	if (m_Collider->getBody()->GetPosition().x > (m_positionCenter.x - m_radius - 0.5) && m_Collider->getBody()->GetPosition().x < (m_positionCenter.x - m_radius + 0.5) && vectorX == true)
	{
		m_Transform.rotation += m_rotate * PI;
		vectorX = false;
	}
	else if (m_Collider->getBody()->GetPosition().x > (m_positionCenter.x + m_radius - 0.5) && m_Collider->getBody()->GetPosition().x < (m_positionCenter.x + m_radius + 0.5) && vectorX == false)
	{
		m_Transform.rotation += m_rotate * PI;
		vectorX = true;
	}
	//printf("%f\n", m_Collider->getBody()->GetPosition().x);
//	printf("%f\n", m_positionCenter.x - m_radius);
	m_Collider->SetVelocity(Vector2(m_radius * cos(m_angle) * 0.6, m_radius * sin(m_angle) / 2));

//	m_Collider->SetVelocity(Vector2(m_radius * cos(m_angle) * 0.5, m_Collider->GetVelocity().y));
//	m_Collider->SetVelocity(Vector2(m_Collider->GetVelocity().x, m_radius * sin(m_angle) * 0.5));

	m_Renderer->Update(deltaTime);

}

void SpinnerFly::OnColliderEnter(GameObject*)
{
}

void SpinnerFly::OnColliderExit(GameObject*)
{
}

SpinnerFly::~SpinnerFly()
{
}
