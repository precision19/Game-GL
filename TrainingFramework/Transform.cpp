#include "stdafx.h"
#include "Transform.h"

Transform::Transform()
{
	position = Vector3(0, 0, 0);
	rotation = Vector3(0, 0, 0);
	scale = Vector3(1, 1, 1);
}

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
