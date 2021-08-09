#pragma once

#include "Object.h"

enum {
	DynamicTrap,
	StaticTrap
};

class Trap : public  Object
{
public:

	Trap();
	~Trap();

	void Draw();
	void Update(float);

};

