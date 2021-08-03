#pragma once
#include "Vertex.h"

class Transform
{
public:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	Matrix GetWorldMatrix();
};

