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
	m_Renderer.at(0)->Draw();
}

void TreasureChest::Update(float deltaTime)
{
	m_Renderer.at(0)->Update(deltaTime);
}
