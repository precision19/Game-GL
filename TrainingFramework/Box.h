#pragma once
#include "box2D/box2d.h"
#include "../Utilities/Math.h"
#include "Object.h"

enum Category {
	CATEGORY_GROUND = 0x0001,
	CATEGORY_PLAYER = 0x0002,
	CATEGORY_NONE = 0x0004,
	CATEGORY_SENSOR = 0x0008,
	CATEGORY_NOTGRAVITY = 0x0010,
	CATEGORY_SENSOR_PLAYER = 0x0020
};

enum Mask {
	MASK_PLAYER = CATEGORY_GROUND | CATEGORY_SENSOR | CATEGORY_NOTGRAVITY,
	MASK_NONE = 0x0000,
	MASK_SENSOR = CATEGORY_GROUND | CATEGORY_PLAYER | CATEGORY_SENSOR_PLAYER,
	MASK_NOTGRAVITY = CATEGORY_PLAYER | CATEGORY_GROUND,
	MASK_SENSOR_PLAYER = CATEGORY_GROUND | CATEGORY_PLAYER
};

class Box 
{
private:
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
public:	
	Box(Object*, float, Category, bool, string);
	Box();
	b2Body* getBody() { return body; };
	b2Fixture* getFixture() { return fixture; };
	void ApplyForce(Vector2);
	Vector2 GetVelocity();
	void SetVelocity(Vector2);
	/*virtual*/ ~Box();
};