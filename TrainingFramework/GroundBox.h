#pragma once
#include "box2D/box2d.h"
#include "../Utilities/Math.h"
#include "Box.h"
class GroundBox : public Box {
public:
	GroundBox();
	~GroundBox();
	void Init(b2World* world, Vector2 position, Vector2 dimension);
};