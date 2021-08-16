#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	m_Name = "Player";
	m_ID = ms_IDMaker;
	ms_IDMaker++;
	m_Collider = NULL;
	m_currentAnimationId = 0;
	canJump = 0;
}

void Player::CreateCollider()
{
	if (m_Collider == NULL)
	{
		m_Collider = new DynamicBox(this, m_ColliderSize, CATEGORY_PLAYER);
	}
	else
	{
		printf("%s already has a collider", m_Name.c_str());
	}
}

void Player::SetSpeed(float speed)
{
	m_Speed = speed;
}

void Player::SetJumpForce(float jumpForce)
{
	m_JumpForce = jumpForce;
}

void Player::AddAnimation(Renderer* renderer)
{
	m_Animations.push_back(renderer);
	if (m_Renderer == NULL)
		m_Renderer = renderer;
}

void Player::Update(float deltaTime)
{
	Vector2 gravity = Vector2(Physic::GetInstance()->GetWorld()->GetGravity().x, Physic::GetInstance()->GetWorld()->GetGravity().y);
	DynamicBox* db = (DynamicBox*)m_Collider;
	SetPosition(Vector3(db->getBody()->GetPosition().x, db->getBody()->GetPosition().y, GetPosition().z));
	if (Input::GetTouch() && canJump > 0)
	{
		float impulse = db->getBody()->GetMass() * 1000;
		db->ApplyForce(Vector2(0.0f, impulse));
	}
	db->SetVelocity(Vector2(70.0f, db->GetVelocity().y));
}

void Player::OnColliderEnter(GameObject* other) {
	if (other->GetName() == "Sensor") {
		Sensor* s = (Sensor*)other;
		if (s->GetPos() == FOOT) { canJump++; }
	}
}

void Player::OnColliderExit(GameObject* other) {
	if (other->GetName() == "Sensor") {
		Sensor* s = (Sensor*)other;
		if (s->GetPos() == FOOT) { canJump--; }
	}
}

Player::~Player()
{
}