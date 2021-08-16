#pragma once
#include "GameObject.h"
#include "DynamicBox.h"

enum Pos {
	HEAD,
	FOOT,
	LEFT,
	RIGHT
};

class Sensor : public GameObject
{
private:
	Pos pos;
public:
	void CreateCollider();
	void Update(float);
	Pos GetPos() { return pos; };
	void SetPos(Pos p) { pos = p; };
	Sensor(Pos);
	~Sensor();
};
