#pragma once
#include "Component.h"
#include "Object.h"


class Player : public Object
{
public:
	int m_Health;
	int m_Life;

	void SetCurrentAnimation();
	void Draw();
	void Update(float);

	Player(int health, int life);
	~Player();
};

