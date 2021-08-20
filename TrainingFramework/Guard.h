#pragma once

#include "GameObject.h"
#include "Physic.h"

class Guard : public GameObject
{
public:
	float m_speed;
	float m_time;
	float veloX;
	bool boolX;
	bool vectorX;
	float m_error; // Sai so

	Vector3 m_positionStart;
	Vector3 m_positionEnd;
	Vector3 m_rotate;

	Guard();

	Guard* Clone();

	void SetPositionStart(Vector3);
	void SetPositionEnd(Vector3);

	void SetSpeed(float);
	void CreateCollider();
	void Update(float);
	~Guard();

};

