#include "stdafx.h"
#include "TreasureChest.h"

TreasureChest::TreasureChest()
{
	m_Name = "Bullet";
	m_ID = ms_IDMaker;
	ms_IDMaker++;
	m_Collider = NULL;
	isWinner = false;
}

TreasureChest::~TreasureChest()
{

}

bool TreasureChest::isCollistion()
{
	return isWinner;
}

void TreasureChest::AddAnimations(Renderer* renderer)
{
	m_Animations.push_back(renderer);
	if (m_Renderer == NULL)
		m_Renderer = renderer;
}

void TreasureChest::CreateCollider()
{
	if (m_Collider == NULL)
	{
		m_Collider = new DynamicBox(this, m_ColliderSize, CATEGORY_NOTGRAVITY);
	}
	else
	{
		printf("%s already have a collider", m_Name.c_str());
	}
}

void TreasureChest::Draw()
{
	m_Renderer->Draw(m_Transform);
}

void TreasureChest::Update(float deltaTime)
{
	if (isCollistion())
	{
		isWinner = true;
	}
	m_Renderer->Update(deltaTime);
}

void TreasureChest::OnColliderEnter(GameObject* other)
{
	if (other->GetName() == "Player")
		isWinner = true;
}

void TreasureChest::OnColliderExit(GameObject*)
{
}
