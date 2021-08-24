#include "stdafx.h"
#include "Animation2D.h"

Animation2D::Animation2D()
{
	m_Name = "Animation 2D";
	m_Model = NULL;
	m_Shaders = NULL;
	m_Texture = NULL;
	m_CurrentSpriteId = 0;
	m_animationCurrent = 0;
	m_FramePerSec = 0;
	m_Loop = true;
}

Animation2D::Animation2D(string name)
{
	m_Name = name;
	m_Model = NULL;
	m_Shaders = NULL;
	m_Texture = NULL;
	m_CurrentSpriteId = 0;
	m_animationCurrent = 0;
	m_FramePerSec = 0;
	m_Loop = true;
}

Renderer* Animation2D::Clone()
{
	Animation2D* result = new Animation2D();
	result->m_Model = m_Model;
	result->m_Shaders = m_Shaders;
	result->m_Texture = m_Texture;
	result->m_Sprites = m_Sprites;
	result->m_CurrentSpriteId = m_CurrentSpriteId;
	result->m_animationCurrent = m_animationCurrent;
	result->m_FramePerSec = m_FramePerSec;
	result->m_Loop = m_Loop;
	return result;
}

void Animation2D::SetTexture(int id)
{
	m_Sprites.push_back(ResourceManager::GetInstance()->GetTexture(id));
	if (m_Texture == NULL)
		m_Texture = m_Sprites.at(0);
}

void Animation2D::SetTexture(string name)
{
	m_Sprites.push_back(ResourceManager::GetInstance()->GetTexture(name));
	if (m_Texture == NULL)
		m_Texture = m_Sprites.at(0);
}

void Animation2D::SetFPS(int fps)
{
	m_FramePerSec = fps;
}

void Animation2D::SetLoop(bool isLoop)
{
	m_Loop = isLoop;
}

void Animation2D::Update(float deltaTime)
{
	if (!m_Loop && End())
		return;

	m_animationCurrent += deltaTime;

	if (m_animationCurrent > 1 / m_FramePerSec)
	{
		m_animationCurrent = 0;
		m_CurrentSpriteId = (m_CurrentSpriteId + 1) % (m_Sprites.size());
		m_Texture = m_Sprites.at(m_CurrentSpriteId);
	}
}

void Animation2D::Reset()
{
	m_Opacity = 1.0;
	m_animationCurrent = 0;
}

bool Animation2D::End()
{
	return m_animationCurrent == m_Sprites.size() - 1;
}

Animation2D::~Animation2D()
{
	
}
