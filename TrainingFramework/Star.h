#pragma once

#include "GameObject.h"
#include "GroundBox.h"
#include "Sensor.h";


class Star : public GameObject
{
public:

	bool isCollisted;
	Star();

	Star* Clone();
	void CreateCollider();
	void Draw();
	void Update(float);
	bool isCollistion();

	void OnColliderEnter(GameObject*);
	void OnColliderExit(GameObject*);

	~Star();
};

