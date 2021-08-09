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
	m_Renderer->Draw();
}

void Trap::Update(float deltaTime)
{
	m_Renderer->Update(deltaTime);
}
