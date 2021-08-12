#pragma once
#include "Object.h"

class Player : public Object
{
protected:
	vector<Renderer*> m_Animations;
	int m_currentAnimationId;
	float m_Speed;
	float m_JumpForce;
public:
	Player();
	void SetSpeed(float);
	void SetJumpForce(float);
	void AddAnimation(Renderer*);
	void Update(float);

	~Player();
};

