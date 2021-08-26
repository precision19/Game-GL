#include "stdafx.h"
#include "Block.h"

Block::Block()
{
	m_Name = "Block";
	m_ID = ms_IDMaker;
	ms_IDMaker++;
	m_Collider = NULL;
	m_Rotate = Vector3(0, 0, 0.5);
}

void Block::SetRenderer(int id)
{
	m_Renderer = m_BlockRender.at(id)->Clone();
}

void Block::SetRenderer(int D, int T, int N , int B)
{
	int count;
	count = D + T + N + B;
	if (count == 4)
	{
		int r = rand() % 2;
		SetRenderer(r);
	}
	else if (count == 3)
	{
		if (B == 0)
			SetRenderer(2);
		else if (N == 0)
		{
			SetRenderer(2);
			m_Transform.rotation += m_Rotate * PI * 2;
		}
		else if (D == 0)
		{
			SetRenderer(2);
			m_Transform.rotation += -m_Rotate * PI;
		}
		else if (T == 0)
		{
			SetRenderer(2);
			m_Transform.rotation += m_Rotate * PI;
		}

	}
	else if (count == 2)
	{
		if (T == 0 && B == 0)
			SetRenderer(3);
		else if (T == 0 && N == 0)
		{
			SetRenderer(3);
			m_Transform.rotation += m_Rotate * PI;
		}
		else if (B == 0 && D == 0)
		{
			SetRenderer(3);
			m_Transform.rotation += -m_Rotate * PI;
		}
		else if (D == 0 && N == 0)
		{
			SetRenderer(3);
			m_Transform.rotation += m_Rotate * PI * 2;
		}
	}
	else
	{
		SetRenderer(1);
	}

}

void Block::SetListRenderer(int id)
{
	m_BlockRender.push_back(PrefabManager::GetInstance()->GetRenderer(id));
}

void Block::SetListRenderer(string name)
{
	m_BlockRender.push_back(PrefabManager::GetInstance()->GetRenderer(name));
}

Object* Block::Clone()
{
	Block* copy = new Block();
	copy->m_ColliderSize = m_ColliderSize;
	copy->m_BlockRender = m_BlockRender;
	return copy;
}

void Block::DestroyCollider()
{
	if (m_Collider) delete m_Collider;
	m_Collider = NULL;
	if (m_Renderer) delete m_Renderer;
	m_Renderer = NULL;

	m_Transform.rotation = Vector3(0, 0, 0);
}

void Block::CreateCollider()
{
	if (m_Collider == NULL)
	{
		m_Collider = new Box(this, m_ColliderSize, CATEGORY_GROUND, false, "Square");
	}
	else
	{
		printf("%s already have a collider", m_Name.c_str()); 
	}
}

Block::~Block()
{
//	m_Renderer == NULL;
}
