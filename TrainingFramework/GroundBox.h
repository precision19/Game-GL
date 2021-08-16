#pragma once
#include "Physic.h"
#include "Object.h"
#include "Sensor.h"

class GroundBox : public Box 
{
protected:
	Sensor* foot;
public:
	GroundBox(Object*, Vector2, Category);
	~GroundBox();
};