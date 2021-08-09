#include "stdafx.h"
#include "Player.h"

Player::Player(int health, int life) : m_Health(health), m_Life(life)
{
	isTouch = false;
}

Player::~Player()
{
}

void Player::Draw()
{
	if (isTouch)
	{
		m_Renderer->Draw();
	}
}

void Player::Update(float deltaTime)
{
	if (!Input::GetTouch())
	{
		isTouch = false;
	}
	else
	{
		isTouch = true;
	}
	m_Renderer->Update(deltaTime);
}
