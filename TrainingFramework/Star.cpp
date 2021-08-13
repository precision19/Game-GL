#include "stdafx.h"
#include "Star.h"

Star::Star()
{
	transform.position -= Vector3(0, 0.5, 0);
}

Star::~Star()
{
}

void Star::Draw()
{
	m_Renderer.at(0)->Draw();
}

void Star::Update(float deltaTime)
{
	m_Renderer.at(0)->Update(deltaTime);
}
