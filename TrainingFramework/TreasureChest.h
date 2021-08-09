#pragma once
#include "Object.h"

class TreasureChest : public Object
{
public:

	TreasureChest();
	~TreasureChest();

	void Draw();
	void Update(float);
};

