#pragma once

#include "Object.h"

class Star : public Object
{
public:

	Star();

	void Draw();
	void Update(float);

	~Star();
};

