#include "stdafx.h"
#include "Star.h"

Star::Star()
{
	m_Name = STAR;
	m_ID = ms_IDMaker;
	ms_IDMaker++;
	m_Collider = NULL;
	isCollisted = false;
	isCollistedOneTime = false;
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
		m_Collider = new Box(this, m_ColliderSize, CATEGORY_SENSOR, true, "Circle");
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
	if (FlagManager::GetInstance()->Check(FLAG_GAME_STATUS, GAME_ON_READY))
	{
		isCollisted = false;
		isCollistedOneTime = false;
	}

	m_Renderer->Update(deltaTime);
}

void Star::OnColliderEnter(GameObject* other) 
{
	if (!isCollistedOneTime)
	{
		if (other->m_Name == PLAYER)
		{
			isCollisted = true;
			isCollistedOneTime = true;
			EventManager::GetInstance()->InvokeEvent(EVENT_GROUP_GAMEPLAY, EVENT_PLAYER_SCORE);
		}
	}
	else
	{
		return;
	}
}

void Star::OnColliderExit(GameObject* other) {
}

void Star::Reset()
{
	isCollisted = false;
	isCollistedOneTime = false;
}
