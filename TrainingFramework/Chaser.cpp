#include "stdafx.h"
#include "Chaser.h"
#include "DynamicBox.h"

Chaser::Chaser() {
	m_Name = "Chaser";
	m_ID = ms_IDMaker;
	ms_IDMaker++;
	m_Collider = NULL;
	m_maxSpeed = 50.0f;
	m_IsReset = 0;
}

Chaser* Chaser::Clone()
{
	Chaser* copy = new Chaser();
	copy->m_Transform = m_Transform;
	copy->m_Renderer = m_Renderer->Clone();
	copy->m_ColliderSize = m_ColliderSize;
	copy->m_speed = m_speed;
	copy->m_positionStart = m_positionStart;
	copy->m_positionTarget = m_positionTarget;
	return copy;
}

void Chaser::SetPositionStart(Vector3 start) {
	m_positionStart = start;
}

void Chaser::CreateCollider() {
	if (m_Collider == NULL)
	{
		m_Collider = new DynamicBox(this, m_ColliderSize, CATEGORY_NOTGRAVITY);
	}
	else
	{
		printf("%s already have a collider", m_Name.c_str());
	}
}

void Chaser::Update(float) {
	if (m_IsReset) {
		m_IsReset = 0;
		Reset();
	}
	Vector2 direction;
	SetPositionTarget(Physic::GetInstance()->GetPositionPlayer());
	direction.x = m_positionTarget.x - GetPosition().x;
	direction.y = m_positionTarget.y - GetPosition().y;
	DynamicBox* db = (DynamicBox *) m_Collider;
	SetPosition(Vector3(db->getBody()->GetPosition().x, db->getBody()->GetPosition().y, GetPosition().z));
	float power;
	if (fabs(direction.x) > m_maxSpeed && fabs(direction.x) > fabs(direction.y)) {
		power = fabs(direction.x) / m_maxSpeed;

	}
	else if (fabs(direction.y) > m_maxSpeed && fabs(direction.y) > fabs(direction.x)) {
		power = fabs(direction.y) / m_maxSpeed;
	}
	else power = 1;
	db->SetVelocity(Vector2(direction.x / power, direction.y / power));
	//printf("%f %f\n", direction.x, direction.y);
}

void Chaser::OnColliderEnter(GameObject* other) {
	if (other->GetName() == "Player") {
		m_IsReset = 1;
	}
}

void Chaser::OnColliderExit(GameObject* other) {
	
}

void Chaser::Reset() {
	((DynamicBox*)m_Collider)->getBody()->SetTransform(b2Vec2(m_positionStart.x, m_positionStart.y), 0.0f);
}

Chaser::~Chaser() {

}
