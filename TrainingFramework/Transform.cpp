#include "stdafx.h"
#include "Transform.h"

Matrix Transform::GetWorldMatrix()
{
	Matrix scaleMatrix, rotationX, rotationY, rotationZ, translation;

	scaleMatrix.SetScale(scale);

	rotationX.SetRotationX(rotation.x);
	rotationY.SetRotationY(rotation.y);
	rotationZ.SetRotationZ(rotation.z);

	translation.SetTranslation(position);

    return scaleMatrix * rotationZ * rotationX * rotationY * translation;
}
