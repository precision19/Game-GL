#include "stdafx.h"
#include "TreasureChest.h"

TreasureChest::TreasureChest()
{
	m_Name = TREASURE_CHEST;
	m_ID = ms_IDMaker;
	ms_IDMaker++;
	m_Collider = NULL;
	isWinner = false;
	m_currentAnimation = 0;
}

TreasureChest::~TreasureChest()
{
	for (int i = 0; i < m_Animations.size(); i++)
		delete m_Animations.at(i);
	m_Animations.clear();

	m_Renderer = NULL;
}

bool TreasureChest::isCollistion()
{
	return isWinner;
}

void TreasureChest::AddAnimations(Renderer* renderer)
{
}

void TreasureChest::SetRenderer(int id)
{
	m_Renderer = PrefabManager::GetInstance()->GetRenderer(id)->Clone();
	m_Animations.push_back(m_Renderer);
}

void TreasureChest::SetRenderer(string name)
{
	m_Renderer = PrefabManager::GetInstance()->GetRenderer(name)->Clone();
	m_Animations.push_back(m_Renderer);
}

void TreasureChest::CreateCollider()
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

void TreasureChest::Draw()
{
	m_Animations.at(m_currentAnimation)->Draw(m_Transform);
}

void TreasureChest::Update(float deltaTime)
{
	if (isCollistion())
	{
		isWinner = true;                                                                                                                                       
	}
	m_Animations.at(m_currentAnimation)->Update(deltaTime);
	//printf("%d\n", m_currentAnimation);
}

void TreasureChest::OnColliderEnter(GameObject* other)
{
	
}

void TreasureChest::OnColliderExit(GameObject*)
{
}
