#pragma once

#include "Object.h"

enum {
	DynamicTrap,
	StaticTrap
};

class Trap : public Object
{
public:
	int currentAnim;
	float m_angle;
	Vector3 m_rotate;
	float m_Frame;

	Trap();
	~Trap();

	Trap* Clone();
	void Draw();
	void Update(float);

};

