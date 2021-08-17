#pragma once

#include "GameObject.h"
#include "Physic.h"

class Bullet : public GameObject
{
protected:
	bool m_IsActive;
	float m_speed;
public:
	Bullet();
	Bullet* Clone();
	void SetSpeed(float);
	void CreateCollider();
	void Update(float);
	void OnColliderEnter(GameObject*);
	~Bullet();
};

