#pragma once
#include "box2D/box2d.h"
#include "../Utilities/Math.h"

enum Category {
	CATEGORY_PLAYER = 0x0001,
	CATEGORY_GROUND = 0x0002,
	CATEGORY_NONE = 0x0004,
	CATEGORY_SENSOR = 0x0008,
	CATEGORY_NOTGRAVITY = 0x0010,
};

enum Mask {
	MASK_PLAYER = 0xFFFF,
	MASK_GROUND = 0xFFFF,
	MASK_NONE = 0x0000,
	MASK_SENSOR = 0xFFFF,
	MASK_NOTGRAVITY = 0xFFFF
};

class Box 
{
private:
	/*bool IsDynamic;*/
public:
	Box();
	virtual ~Box();
	virtual void Update(float);
	//virtual void Init(b2World* world, Vector2 position, Vector2 dimension);
	//int GetDynmaic() { return IsDynamic; }
	//void SetDynamic(bool dynamic) { IsDynamic = dynamic; }
};