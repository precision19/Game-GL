#pragma once
#include "Vertex.h"

class Transform
{
public:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	Transform();

	Matrix GetWorldMatrix();
	Matrix GetWorldMatrix(Vector3);
};

