#include "stdafx.h"
#include "Block.h"
#include "GroundBox.h"

Block::Block()
{
	m_Name = "Block";
	m_ID = ms_IDMaker;
	ms_IDMaker++;
	m_Collider = NULL;
}

Object* Block::Clone()
{
	Block* copy = new Block();
	copy->m_Transform = m_Transform;
	copy->m_Renderer = m_Renderer->Clone();
	copy->m_ColliderSize = m_ColliderSize;
	return copy;
}

void Block::CreateCollider()
{
	if (m_Collider == NULL)
	{
		m_Collider = new GroundBox(this, Vector2(m_ColliderSize, m_ColliderSize), CATEGORY_GROUND);
	}
	else
	{
		printf("%s already have a collider", m_Name.c_str());
	}
}
