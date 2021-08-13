#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	m_currentAnimationId = 0;
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
	if (Input::GetTouch() && m_currentAnimationId == 0)
	{
		m_currentAnimationId = 1;
		m_Renderer = m_Animations.at(m_currentAnimationId);
	}
	else if (!Input::GetTouch() && m_currentAnimationId == 1)
	{
		m_currentAnimationId = 0;
		m_Renderer = m_Animations.at(m_currentAnimationId);
	}

}

Player::~Player()
{
}