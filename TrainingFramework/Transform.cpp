#include "stdafx.h"
#include "Transform.h"

Transform::Transform()
{
	position = Vector3(0, 0, 0);
	rotation = Vector3(0, 0, 0);
	scale = Vector3(1, 1, 1);
}

Transform::Transform(const Transform& transform)
{
	position.x = transform.position.x;
	position.y = transform.position.y;
	position.z = transform.position.z;

	rotation.x = transform.rotation.x;
	rotation.y = transform.rotation.y;
	rotation.z = transform.rotation.z;

	scale.x = transform.scale.x;
	scale.y = transform.scale.y;
	scale.z = transform.scale.z;
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

void Transform::Reset()
{
	position = Vector3(0, 0, 0);
	rotation = Vector3(0, 0, 0);
	scale = Vector3(1, 1, 1);
}
