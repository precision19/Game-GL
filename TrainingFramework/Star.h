#pragma once

#include "GameObject.h"


class Star : public GameObject
{
public:

	bool isCollisted;
	bool isCollistedOneTime;
	Star();

	Star* Clone();
	void CreateCollider();
	void Draw();
	void Update(float);

	void OnColliderEnter(GameObject*);
	void OnColliderExit(GameObject*);
	void Reset();
	~Star();
};

