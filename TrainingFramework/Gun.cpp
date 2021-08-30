#include "stdafx.h"
#include "Gun.h"

Gun::Gun()
{
	m_time = 0;
	m_Name = "Gun";
	m_ID = ms_IDMaker;
	ms_IDMaker++;
	m_Collider = NULL;
}

Gun* Gun::Clone()
{
	Gun* copy = new Gun();
	copy->m_Transform = m_Transform;
	copy->m_Renderer = m_Renderer->Clone();
	copy->m_ColliderSize = m_ColliderSize;
	return copy;
}

void Gun::SetAttackSpeed(float)
{
}

void Gun::CreateCollider()
{
	if (m_Collider == NULL)
	{
		m_Collider = new Box(this, m_ColliderSize, CATEGORY_NONE, true, "Circle");
	}
	else
	{
		printf("%s already have a collider", m_Name.c_str());
	}
}

void Gun::SetDirection(Direction dir) {
	if (dir == EAST) {
		SetRotation(Vector3(0.0f, 0.0f, -90.0f));
	}
	if (dir == WEST) {
		SetRotation(Vector3(0.0f, 0.0f, 90.0f));
	}
	if (dir == NORTH) {
		SetRotation(Vector3(0.0f, 0.0f, 0.0f));
	}
	if (dir == SOUTH) {
		SetRotation(Vector3(0.0f, 0.0f, 180.0f));
	}
	direction = dir;
}

void Gun::Update(float deltaTime)
{	
	//printf("%d\n", direction);
	m_time += deltaTime;
	if (m_time > 1.9f) {
		for each (Bullet * b in bullets) {
			//b->Update(deltaTime);
			if (b->GetIsRender() == false) {
				b->SetIsRender(true);
				break;
			}
		}
		m_time -= 1.9f;
	}
	for each (Bullet * b in bullets) {
		if (b->GetIsRender() == false) {
			b->GetColliderBox()->getBody()->SetTransform(b2Vec2(b->GetBasePosition().x, b->GetBasePosition().y), 0);
			b->SetPosition(b->GetBasePosition());
		}
	}
	m_Renderer->Update(deltaTime);
}

void Gun::Draw()
{
	m_Renderer->Draw(m_Transform);
	for each (Bullet * b in bullets) {
		b->Draw();
	}
}

Gun::~Gun()
{
	/*for each (Bullet * bullet in bullets) {
		delete bullet;
	}*/
}
