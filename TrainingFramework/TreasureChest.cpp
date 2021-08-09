#include "stdafx.h"
#include "TreasureChest.h"

TreasureChest::TreasureChest()
{
}

TreasureChest::~TreasureChest()
{
}

void TreasureChest::Draw()
{
	m_Renderer->Draw();
}

void TreasureChest::Update(float deltaTime)
{
	m_Renderer->Update(deltaTime);
}
