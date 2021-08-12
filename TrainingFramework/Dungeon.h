#pragma once
#include "../Utilities/utilities.h"
#include <math.h>

class Dungeon
{
public:
	static const int Height = 8;
	static const int Width = 14;

	static const int CellSize = 64;

	static Vector3 GirdToWord(float, float, float);
};

