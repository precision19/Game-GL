#include "stdafx.h"
#include "Object.h"

Object::Object()
{
	currentAnim = 0;
	i = 0;
}

void Object::SetNativeSize(int k)
{
	if (currentAnim == k)
	{
		Vector3 size = m_Renderer.at(k)->GetSize();		
		//printf("%f %f\n", size.x, size.y);

	}
}

void Object::SetCurrentAnimation(int keys)
{
	if (VK_SPACE)
	{
		currentAnim = 1;
	}
	else
	{
		currentAnim = 0;
	}

}

void Object::SetPosition(Vector3 position)
{
	transform.position = position;
}

Vector3 Object::GetPosition() 
{
	return transform.position;
}

void Object::SetScale(Vector3 scale)
{
	transform.scale = scale;
}

void Object::SetRotation(Vector3 rotation)
{
	transform.rotation = rotation * PI / 180;
}

void Object::SetRenderer(int id)
{
	m_Renderer.push_back(PrefabManager::GetInstance()->GetRenderer(id));
	m_Renderer.at(i)->SetTransform(&transform);
	++i;
}

void Object::Draw()
{
	m_Renderer.at(currentAnim)->Draw();
}

void Object::Update(float deltaTime)
{
	m_Renderer.at(currentAnim)->Update(deltaTime);
}

Object::~Object()
{
	for (int i = 0; i < m_Renderer.size(); i++)
	{
		delete m_Renderer.at(i);
	}
	m_Renderer.clear();

}
