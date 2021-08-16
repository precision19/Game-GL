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
	MASK_GROUND = 0xFFFE,
	MASK_NONE = 0x0000,
	MASK_SENSOR = 0x0001,
	MASK_NOTGRAVITY = 0xFFFF
};

class Box 
{
private:

public:
	Box();
	virtual ~Box();
};