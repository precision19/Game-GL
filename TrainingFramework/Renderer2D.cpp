#include "stdafx.h"
#include "Renderer2D.h"

Renderer2D::Renderer2D()
{
	m_Model = ResourceManager::GetInstance()->GetModel("Sprite");
	m_Shaders = ResourceManager::GetInstance()->GetShaders("Sprite");
	m_Texture = NULL;
	m_CurrentSpriteId = 0;
	m_animationCurrent = 0;
	m_FramePerSec = 0;
}

void Renderer2D::SetTexture(int spriteId)
{
	m_Sprites.push_back(ResourceManager::GetInstance()->GetTexture(spriteId));
	if (m_Texture == NULL)
		m_Texture = m_Sprites.at(0);
}

void Renderer2D::SetTexture(string spriteName)
{
	m_Sprites.push_back(ResourceManager::GetInstance()->GetTexture(spriteName));
	if (m_Texture == NULL)
		m_Texture = m_Sprites.at(0);
}

float Renderer2D::GetFramePerSecond()
{
	m_FramePerSec = Renderer::m_FramePerSec;
	return 1 / m_FramePerSec;
}

Vector3 Renderer2D::GetSize()
{
	Vector3 size = m_Texture->GetSize();
	size = Vector3(size.x * transform->scale.x, size.y * transform->scale.y, size.z * transform->scale.z);
	return size;
}

Matrix Renderer2D::GetWVP()
{
	Matrix WVP = transform->GetWorldMatrix(m_Texture->GetSize()) * Camera::GetInstance()->GetViewMatrix() * Camera::GetInstance()->GetProjection();
	return WVP;
}

void Renderer2D::Update(float deltaTime)
{
	m_animationCurrent += deltaTime;
	float FPS = GetFramePerSecond();

	if (m_animationCurrent > FPS)
	{
		m_CurrentSpriteId = (m_CurrentSpriteId + 1) % (m_Sprites.size());
		m_animationCurrent = 0;
	}
	m_Texture = m_Sprites.at(m_CurrentSpriteId);
}

Renderer2D::~Renderer2D()
{
	m_Model = NULL;
	m_Texture = NULL;
	m_Sprites.clear();
	m_Shaders = NULL;
}
