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

Matrix Transform::GetWorldMatrix(Vector3 multiScale)
{
	Matrix scaleMatrix, rotationX, rotationY, rotationZ, translation;
	
	scaleMatrix.SetScale(scale.x * multiScale.x, scale.y * multiScale.y, scale.z * multiScale.z);

	rotationX.SetRotationX(rotation.x);
	rotationY.SetRotationY(rotation.y);
	rotationZ.SetRotationZ(rotation.z);

	translation.SetTranslation(position);

	return scaleMatrix * rotationZ * rotationX * rotationY * translation;
}
