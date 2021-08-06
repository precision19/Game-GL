#pragma once
#include "box2D/box2d.h"
#include "../Utilities/Math.h"
class Box {
private:
	bool IsDynamic;
public:
	Box();
	virtual ~Box();
	virtual void Init(b2World* world, Vector2 position, Vector2 dimension);
	int GetDynmaic() { return IsDynamic; }
	void SetDynamic(bool dynamic) { IsDynamic = dynamic; }
};