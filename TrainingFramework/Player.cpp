#include "stdafx.h"
#include "Player.h"

Player::Player(int health, int life) : m_Health(health), m_Life(life)
{
	currentAnim = 0;
	
}

Player::~Player()
{
}

void Player::SetCurrentAnimation()
{
	if (GetAsyncKeyState(VK_SPACE))
	{
		currentAnim = 1;
	}
	else
	{
		currentAnim = 0;
	}
}

void Player::Draw()
{
	m_Renderer.at(currentAnim)->Draw();
}

void Player::Update(float deltaTime)
{
	m_Renderer.at(currentAnim)->Update(deltaTime);
	this->SetCurrentAnimation();
}
