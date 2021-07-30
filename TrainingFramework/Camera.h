#pragma once
#include "Vertex.h"
#include "Globals.h"
#include <string>
#include "Input.h"

class Camera
{
protected:
	static Camera * ms_Instance;

	Vector3 m_Position;
	Vector3 m_Target;
	Vector3 m_Up;

	Matrix m_WorldMatrix;
	Matrix m_ViewMatrix;
	Matrix m_Projection;

	float m_Near;
	float m_Far;
	float m_FOV;

	float m_Speed;
	float m_RotateSpeed;

	float m_FaceAngle;

	bool m_IsPerspective;

	void SetWorldMatrix();
	void SetViewMatrix();
public:
	static void CreateInstance();
	static Camera* GetInstance();
	static void DestroyInstance();

	Camera();
	Camera(int);
	void Init();
	Vector3 GetPosition();
	void SetPosition(Vector3);
	void SetTarget(Vector3);
	void SetUpVector(Vector3);
	void SetFOVY(float);
	void SetNear(float);
	void SetFar(float);
	void SetMoveSpeed(float);
	void SetRotateSpeed(float);
	Matrix GetWorldMatrix();
	Matrix GetViewMatrix();
	Matrix GetProjection();
	void Update(float);
};

