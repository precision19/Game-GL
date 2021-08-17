#include "stdafx.h"
#include "Star.h"

Star::Star()
{
	m_Name = "Star";
	m_ID = ms_IDMaker;
	ms_IDMaker++;
	m_Collider = NULL;
	isCollisted = false;
}

Star* Star::Clone()
{
	Star* copy = new Star();
	copy->m_Transform = m_Transform;
	copy->m_Renderer = m_Renderer->Clone();
	copy->m_ColliderSize = m_ColliderSize;
	return copy;
}


void Star::CreateCollider()
{
	if (m_Collider == NULL)
	{
		m_Collider = new GroundBox(this, Vector2(m_ColliderSize, m_ColliderSize), CATEGORY_NONE);
	}
	else
	{
		printf("%s already have a collider", m_Name.c_str());
	}
}

Star::~Star()
{
//	delete circle;
}

void Star::Draw()
{
	if (!isCollisted)
	{
		m_Renderer->Draw(m_Transform);
	}	
}

void Star::Update(float deltaTime)
{
	m_Renderer->Update(deltaTime);
	if (isCollistion())
	{
		isCollisted = true;
	}	
}

bool Star::isCollistion()
{
	return isCollisted;
}

void Star::OnColliderEnter(GameObject* other) {
	if (other->GetName() == "Player")
		isCollisted = true;
}

void Star::OnColliderExit(GameObject* other) {
}