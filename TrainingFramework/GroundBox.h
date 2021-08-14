#pragma once
#include "Physic.h"
#include "Object.h"

class GroundBox : public Box 
{
public:
	GroundBox(Object*, Vector2, Category);
	~GroundBox();
};