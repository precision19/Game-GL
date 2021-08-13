#pragma once
#include "Physic.h"
#include "Object.h"

class GroundBox : public Box 
{
public:
	GroundBox(Object*, Vector2, Category);
	~GroundBox();
	//void Init(b2World* world, Vector2 position, Vector2 dimension, Object* obj);
};