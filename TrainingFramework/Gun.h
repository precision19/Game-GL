#pragma once

#include "GameObject.h"
#include "Physic.h"
#include "Bullet.h"
#include <vector>

enum Direction {
	EAST, //-90
	WEST, //90
	NORTH, //0
	SOUTH, //180
};

class Gun : public GameObject
{
protected:
	Direction direction;
public:
	vector<Bullet*> bullets;
	float m_time;

	Gun();

	Gun* Clone();

	void SetDirection(Direction dir);
	Direction GetDirection() { return direction; }
	void SetAttackSpeed(float);
	void CreateCollider();
	void Update(float);
	void Draw();
	void DestroyCollider();
	~Gun();

};

