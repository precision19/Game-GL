#include "stdafx.h"
#include "Player.h"

Player::Player(int health, int life) : m_Health(health), m_Life(life)
{
	currentAnim = 1;
}

Player::~Player()
{
}

void Player::Draw()
{
	m_Renderer.at(currentAnim)->Draw();
}

void Player::Update(float deltaTime)
{
	m_Renderer.at(currentAnim)->Update(deltaTime);
}
