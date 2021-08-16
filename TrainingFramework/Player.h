#pragma once
#include "GameObject.h"

class Player : public GameObject
{
protected:
	vector<Renderer*> m_Animations;
	int m_currentAnimationId;
	float m_Speed;
	float m_JumpForce;
public:
	Player();
	void CreateCollider();
	void SetSpeed(float);
	void SetJumpForce(float);
	void AddAnimation(Renderer*);
	void Update(float);

	~Player();
};

