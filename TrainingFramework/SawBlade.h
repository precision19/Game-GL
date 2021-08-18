#pragma once
#include "GameObject.h"
#include "DynamicBox.h"

class SawBlade : public GameObject
{
public:
	float m_Time;
	float m_angle;
	Vector3 m_rotate;

	SawBlade();
	~SawBlade();
	
	void CreateCollider();
	SawBlade* Clone();
	void Draw();
	void Update(float);
};

