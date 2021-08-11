#include "stdafx.h"
#include "Trap.h"

Trap::Trap()
{
}

Trap::~Trap()
{
}

void Trap::Draw()
{
	m_Renderer.at(0)->Draw();
}

void Trap::Update(float deltaTime)
{
	m_Renderer.at(0)->Update(deltaTime);
}
