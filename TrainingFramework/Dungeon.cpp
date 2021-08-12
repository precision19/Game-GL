#include "stdafx.h"
#include "Dungeon.h"

Vector3 Dungeon::GirdToWord(float x, float y, float z)
{
	float h = Height, w = Width;

	float Ox = -w / 2 * CellSize;
	float Oy = -h / 2 * CellSize;
	Vector3 result = Vector3(Ox + CellSize / 2 + x * CellSize, Oy + CellSize / 2 + y * CellSize, z);
	return result;
}
