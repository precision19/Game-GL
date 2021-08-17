#pragma once

#include "GameObject.h"
#include "Physic.h"
#include "Bullet.h"

class Gun : public GameObject
{
protected:
	float m_Timer;
	float m_Cooldown;
public:
	Gun();
	GameObject* Clone();
	void Update(float);
	~Gun();

};

