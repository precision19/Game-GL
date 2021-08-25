#pragma once
#include "GameObject.h"
#include "Physic.h"

class DynamicBlade : public GameObject
{
public:
	float m_speed;
	bool boolY;
	bool vectorY;

	Vector3 m_positionStart;
	Vector3 m_positionEnd;
	Vector3 m_rotate;

	DynamicBlade();

	DynamicBlade* Clone();

	void SetPositionStart(Vector3);
	void SetPositionEnd(Vector3);

	void SetSpeed(float);
	void CreateCollider();
	void Update(float);
	~DynamicBlade();

};

