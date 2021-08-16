#pragma once

#include "GameObject.h"
#include "Physic.h"
#include "Bullet.h"

class Gun : public GameObject
{
public:

	float m_time;

	Gun();

	Gun* Clone();
	void CreateCollider();
	void Update(float);
	void Draw();
	~Gun();

};

