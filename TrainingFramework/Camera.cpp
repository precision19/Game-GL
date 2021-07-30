#include "stdafx.h"
#include "Camera.h"

Camera* Camera::ms_Instance = NULL;

void Camera::SetWorldMatrix()
{
	Vector3 zaxis = (m_Position - m_Target).Normalize();
	Vector3 xaxis = (m_Up.Cross(zaxis)).Normalize();
	Vector3 yaxis = (zaxis.Cross(xaxis)).Normalize();

	m_WorldMatrix.m[0][0] = xaxis.x;
	m_WorldMatrix.m[0][1] = xaxis.y;
	m_WorldMatrix.m[0][2] = xaxis.z;
	m_WorldMatrix.m[0][3] = 0;

	m_WorldMatrix.m[1][0] = yaxis.x;
	m_WorldMatrix.m[1][1] = yaxis.y;
	m_WorldMatrix.m[1][2] = yaxis.z;
	m_WorldMatrix.m[1][3] = 0;

	m_WorldMatrix.m[2][0] = zaxis.x;
	m_WorldMatrix.m[2][1] = zaxis.y;
	m_WorldMatrix.m[2][2] = zaxis.z;
	m_WorldMatrix.m[2][3] = 0;

	m_WorldMatrix.m[3][0] = m_Position.x;
	m_WorldMatrix.m[3][1] = m_Position.y;
	m_WorldMatrix.m[3][2] = m_Position.z;
	m_WorldMatrix.m[3][3] = 1;
}

void Camera::SetViewMatrix()
{
	Vector3 zaxis = (m_Position - m_Target).Normalize();
	Vector3 xaxis = (m_Up.Cross(zaxis)).Normalize();
	Vector3 yaxis = (zaxis.Cross(xaxis)).Normalize();

	m_ViewMatrix.m[0][0] = xaxis.x;
	m_ViewMatrix.m[0][1] = yaxis.x;
	m_ViewMatrix.m[0][2] = zaxis.x;
	m_ViewMatrix.m[0][3] = 0;

	m_ViewMatrix.m[1][0] = xaxis.y;
	m_ViewMatrix.m[1][1] = yaxis.y;
	m_ViewMatrix.m[1][2] = zaxis.y;
	m_ViewMatrix.m[1][3] = 0;

	m_ViewMatrix.m[2][0] = xaxis.z;
	m_ViewMatrix.m[2][1] = yaxis.z;
	m_ViewMatrix.m[2][2] = zaxis.z;
	m_ViewMatrix.m[2][3] = 0;

	m_ViewMatrix.m[3][0] = -m_Position.Dot(xaxis);
	m_ViewMatrix.m[3][1] = -m_Position.Dot(yaxis);
	m_ViewMatrix.m[3][2] = -m_Position.Dot(zaxis);
	m_ViewMatrix.m[3][3] = 1;
}

void Camera::CreateInstance()
{
	if (ms_Instance == NULL)
		ms_Instance = new Camera();
}

Camera* Camera::GetInstance()
{
	return ms_Instance;
}

void Camera::DestroyInstance()
{
	if (ms_Instance)
	{
		delete ms_Instance;
		ms_Instance = NULL;
	}
}

Camera::Camera()
{
	m_FaceAngle = 0;
}

Camera::Camera(int isPerspective)
{
	m_IsPerspective = isPerspective;
}

void Camera::Init()
{
	m_Up = Vector3(0, 1, 0);
	m_Near = 0.1;
	m_Far = 500.0;
	m_FaceAngle = 0;
	m_RotateSpeed = 1;

	SetWorldMatrix();
	SetViewMatrix();

	if (m_IsPerspective)
	{
		m_Projection.SetPerspective(m_FOV, (float)Globals::screenWidth / (float)Globals::screenHeight, m_Near, m_Far);
	}
	else
	{
		m_Projection.SetOrtho((float)Globals::screenWidth, (float)Globals::screenHeight, m_Near, m_Far);
	}
}

Vector3 Camera::GetPosition()
{
	return m_Position;
}

void Camera::SetPosition(Vector3 position)
{
	m_Position = position;
}

void Camera::SetTarget(Vector3 target)
{
	m_Target = target;
}

void Camera::SetUpVector(Vector3 up)
{
	m_Up = up;
}

void Camera::SetFOVY(float fovY)
{
	m_FOV = fovY;
}

void Camera::SetNear(float fNear)
{
	m_Near = fNear;
}

void Camera::SetFar(float fFar)
{
	m_Far = fFar;
}

void Camera::SetMoveSpeed(float speed)
{
	m_Speed = speed;
}

void Camera::SetRotateSpeed(float rotateSpeed)
{
	m_RotateSpeed = rotateSpeed;
}

Matrix Camera::GetWorldMatrix()
{
	return m_WorldMatrix;
}

Matrix Camera::GetViewMatrix()
{
	return m_ViewMatrix;
}

Matrix Camera::GetProjection()
{
	return m_Projection;
}

void Camera::Update(float deltaTime)
{
	Vector3 zaxis = (m_Position - m_Target).Normalize();
	Vector3 xaxis = (m_Up.Cross(zaxis)).Normalize();

	Vector3 movement;
	if (Input::GetKeyDown(W))
		movement -= zaxis;
	if (Input::GetKeyDown(S))
		movement += zaxis;
	if (Input::GetKeyDown(A))
		movement -= xaxis;
	if (Input::GetKeyDown(D))
		movement += xaxis;

	movement.y = 0;
	movement.Normalize();
	m_Position += movement * m_Speed * deltaTime;
	m_Target += movement * m_Speed * deltaTime;

	// Bay
	float y = 0;
	if (Input::GetKeyDown(Space))
		y += 1;
	if (Input::GetKeyDown(Ctrl))
		y -= 1;

	m_Position.y += y * m_Speed * deltaTime;
	m_Target.y += y * m_Speed * deltaTime;

	SetWorldMatrix();
	SetViewMatrix();

	float angle = 0;
	if (Input::GetKeyDown(Left))
		angle += m_RotateSpeed * deltaTime;
	if (Input::GetKeyDown(Right))
		angle -= m_RotateSpeed * deltaTime;

	float angle2 = 0;
	if (Input::GetKeyDown(Up))
	{
		m_FaceAngle -= m_RotateSpeed * deltaTime;
		angle2 -= m_RotateSpeed * deltaTime;
	}
	if (Input::GetKeyDown(Down))
	{
		m_FaceAngle += m_RotateSpeed * deltaTime;
		angle2 += m_RotateSpeed * deltaTime;
	}

	if (m_FaceAngle > 89 * (PI / 180))
	{
		m_FaceAngle -= m_RotateSpeed * deltaTime;
		angle2 -= m_RotateSpeed * deltaTime;
	}
	else if (m_FaceAngle < -89 * (PI / 180))
	{
		m_FaceAngle += m_RotateSpeed * deltaTime;
		angle2 += m_RotateSpeed * deltaTime;
	}
	
	Vector4 localTarget = Vector4(0, 0, -(m_Position - m_Target).Length(), 1);
	Vector4 Oy = Vector4(0, 1, 0, 0);
	
	Vector4 rotationAxis = Oy * m_ViewMatrix;
	Matrix rotation;
	Vector4 newLocalTarget = localTarget * rotation.SetRotationAngleAxis(angle, rotationAxis.x, rotationAxis.y, rotationAxis.z);

	Vector3 v3LocalTarget = Vector3(localTarget.x, localTarget.y, localTarget.z);
	Vector3 v3Oy = Vector3(0, 1, 0);
	Vector3 v3Ox = v3Oy.Cross(v3LocalTarget);
	Vector4 v4Ox = Vector4(v3Ox.x, v3Ox.y, v3Ox.z, 0);

	Vector4 newLocalTarget2 = newLocalTarget * rotation.SetRotationAngleAxis(angle2, v4Ox.x, v4Ox.y, v4Ox.z);

	Vector4 newWorldTarget = newLocalTarget2 * m_WorldMatrix;

	m_Target = Vector3(newWorldTarget.x, newWorldTarget.y, newWorldTarget.z);

	SetWorldMatrix();
	SetViewMatrix();
}
