#pragma once
#include "Physic.h"
#include "Object.h"
#include "Sensor.h"

class GroundBox : public Box 
{
public:
	GroundBox(Object*, Vector2, Category);
	~GroundBox();
	Sensor* foot;
};