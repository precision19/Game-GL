#pragma once
#include "GameObject.h"
#include "DynamicBox.h"

enum Pos {
	HEAD,
	FOOT,
	SIDE,
	OTHER
};

class Sensor : public GameObject
{
private:
	Pos pos;
	int numContact;
public:
	void CreateCollider();
	void Update(float);
	Pos GetPos() { return pos; };
	void SetPos(Pos p) { pos = p; };
	int GetNumContact() { return numContact; };
	Sensor(Pos);
	~Sensor();
	void OnColliderEnter(GameObject*);
	void OnColliderExit(GameObject*);
};
