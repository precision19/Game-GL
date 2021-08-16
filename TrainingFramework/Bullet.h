#pragma once

#include "GameObject.h"
#include "Physic.h"

class Bullet : public GameObject
{
public:
	float m_time;
	float m_speed;

	Bullet();

	Bullet* Clone();
	void SetSpeed(float);
	void CreateCollider();
	void Update(float);
	~Bullet();
};

