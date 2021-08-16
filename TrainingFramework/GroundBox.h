#pragma once
#include "Physic.h"
#include "Object.h"
#include "Sensor.h"

class GroundBox : public Box 
{
protected:
	b2Body* groundBody;
public:
	GroundBox(Object*, Vector2, Category);
	~GroundBox();
	b2Body* getBody() { return groundBody; };
};