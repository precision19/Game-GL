#pragma once
#include "Component.h"
#include "Object.h"

enum{
	Run,
	Jump
};

class Player : public Object
{
public:
	int m_Health;
	int m_Life;
	bool isTouch;

	void Navigation(); // chuyen huong di chuyen
	void Draw();
	void Update(float);

	Player(int health, int life);
	~Player();
};

