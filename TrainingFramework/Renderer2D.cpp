#include "stdafx.h"
#include "Renderer2D.h"

Renderer2D::Renderer2D()
{
	m_Model = ResourceManager::GetInstance()->GetModel("Sprite");
	m_Shaders = ResourceManager::GetInstance()->GetShaders("Sprite");
	m_Texture = NULL;
	m_CurrentSpriteId = 0;
	anim_cursor = 0;
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
	anim_cursor += deltaTime;
	if (anim_cursor)
	{
		m_CurrentSpriteId = (m_CurrentSpriteId + 1) % (m_Sprites.size());
		anim_cursor = 0;
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
