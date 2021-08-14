#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	m_Name = "Player";
	m_ID = ms_IDMaker;
	ms_IDMaker++;
	m_Collider = NULL;
	m_currentAnimationId = 0;
}

void Player::CreateCollider()
{
	if (m_Collider == NULL)
	{
		m_Collider = new DynamicBox(this, m_ColliderSize, CATEGORY_PLAYER);
		Physic::GetInstance()->AddBox(m_Collider);
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
	// TEST
	if (Input::GetTouch())
	{
		((DynamicBox*)m_Collider)->ApplyForce(Vector2(70.0f, 8000.0f));
	}
}

Player::~Player()
{
}